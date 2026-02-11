resolve_result_relay_cb (GrlSource *source,
                         guint operation_id,
                         GrlMedia *media,
                         gpointer user_data,
                         const GError *error)
{
  struct ResolveRelayCb *rrc = (struct ResolveRelayCb *) user_data;
  GList *each_key;
  GList *delete_key;

  GRL_DEBUG (__FUNCTION__);

  if (!operation_is_cancelled (operation_id)) {

    each_key = rrc->keys;
    while (each_key) {
      if (grl_data_has_key (GRL_DATA (media), GRLPOINTER_TO_KEYID (each_key->data))) {
        map_update_known_key (rrc->map, GRLPOINTER_TO_KEYID (each_key->data), media);
        delete_key = each_key;
        each_key = g_list_next (each_key);
        rrc->keys = g_list_delete_link (rrc->keys, delete_key);
      } else {
        map_update_unknown_key (rrc->map, GRLPOINTER_TO_KEYID (each_key->data), source);
        each_key = g_list_next (each_key);
      }
    }

    g_hash_table_remove (rrc->resolve_specs, source);
  }

  operation_set_finished (operation_id);

  if (operation_is_cancelled (rrc->operation_id) &&
      !rrc->cancel_invoked) {
    rrc->cancel_invoked = TRUE;
    g_hash_table_foreach (rrc->resolve_specs, (GHFunc) cancel_resolve_spec, NULL);
  }

  if (error && source == rrc->source && !rrc->error) {

    rrc->error = g_error_copy (error);
  }

  if (g_hash_table_size (rrc->resolve_specs) == 0 && !rrc->specs_to_invoke) {

    if (!operation_is_cancelled (rrc->operation_id)) {
      each_key = rrc->keys;
      while (each_key) {
        if (map_sources_to_specs (rrc->resolve_specs, rrc->map, media,
                                  GRLPOINTER_TO_KEYID (each_key->data),
                                  rrc->options, rrc)) {
          each_key = g_list_next (each_key);
        } else {
          delete_key = each_key;
          each_key = g_list_next (each_key);
          rrc->keys = g_list_delete_link (rrc->keys, delete_key);
        }
      }

    }

    rrc->specs_to_invoke = g_hash_table_get_values (rrc->resolve_specs);
    if (rrc->specs_to_invoke) {
      guint id;
      id = g_idle_add_full (grl_operation_options_get_flags (rrc->options) & GRL_RESOLVE_IDLE_RELAY?
                            G_PRIORITY_DEFAULT_IDLE: G_PRIORITY_HIGH_IDLE,
                            resolve_idle,
                            rrc,
                            NULL);
      g_source_set_name_by_id (id, "[grilo] resolve_idle");
    } else {
      guint id;
      id = g_idle_add_full (grl_operation_options_get_flags (rrc->options) & GRL_RESOLVE_IDLE_RELAY?
                            G_PRIORITY_DEFAULT_IDLE: G_PRIORITY_HIGH_IDLE,
                            resolve_all_done,
                            rrc,
                            NULL);
      g_source_set_name_by_id (id, "[grilo] resolve_all_done");
    }
  }
}
