grl_tracker_source_resolve (GrlSource *source,
                            GrlSourceResolveSpec *rs)
{
  GrlTrackerSourcePriv *priv               = GRL_TRACKER_SOURCE_GET_PRIVATE (source);
  gchar                *constraint         = NULL, *sparql_select, *sparql_final;
  gchar                *sparql_type_filter = NULL;
  const gchar          *url                = grl_media_get_url (rs->media);
  GrlTrackerOp         *os;

  GRL_IDEBUG ("%s: id=%i", __FUNCTION__, rs->operation_id);


  if (g_strcmp0 (priv->tracker_datasource, grl_source_get_id (rs->source)) == 0) {
    if (grl_media_get_id (rs->media) == NULL) {
      if (grl_tracker_per_device_source) {
        constraint = grl_tracker_source_get_device_constraint (priv);
        sparql_select = grl_tracker_source_get_select_string (rs->keys);
        sparql_type_filter = get_sparql_type_filter (rs->options, TRUE);
        sparql_final = g_strdup_printf (TRACKER_BROWSE_FILESYSTEM_ROOT_REQUEST,
                                        sparql_select,
                                        grl_tracker_show_documents? TRACKER_BROWSE_SHOW_DOCUMENTS: "",
                                        sparql_type_filter,
                                        constraint, 0, 1);
      } else {
        rs->callback (rs->source, rs->operation_id, rs->media, rs->user_data, NULL);
        return;
      }
    } else {
      sparql_select = grl_tracker_source_get_select_string (rs->keys);
      sparql_final = g_strdup_printf (TRACKER_RESOLVE_REQUEST, sparql_select,
                                      grl_media_get_id (rs->media));
    }
  } else {
    if (url) {
      sparql_select = grl_tracker_source_get_select_string (rs->keys);
      sparql_final = g_strdup_printf (TRACKER_RESOLVE_URL_REQUEST,
                                      sparql_select, url);
    } else {
      rs->callback (rs->source, rs->operation_id, rs->media, rs->user_data, NULL);
      return;
    }
  }

  GRL_IDEBUG ("\request: '%s'", sparql_final);

  os = grl_tracker_op_initiate_metadata (sparql_final,
                                         (GAsyncReadyCallback) tracker_resolve_cb,
                                         rs);
  os->keys = rs->keys;

  grl_tracker_queue_push (grl_tracker_queue, os);

  g_clear_pointer (&sparql_type_filter, g_free);
  g_clear_pointer (&constraint, g_free);
  g_clear_pointer (&sparql_select, g_free);
}
