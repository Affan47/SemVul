source_added_cb (GrlRegistry *registry, GrlSource *source, gpointer user_data)
{
  static gboolean first = TRUE;
  GList * keys = grl_metadata_key_list_new (GRL_METADATA_KEY_TITLE,
					    GRL_METADATA_KEY_DURATION,
					    GRL_METADATA_KEY_URL,
					    GRL_METADATA_KEY_CHILDCOUNT,
					    GRL_METADATA_KEY_INVALID);
  g_debug ("Detected new source available: '%s'",
           grl_source_get_name (source));


  if (first &&
      grl_source_supported_operations (source) & GRL_OP_BROWSE) {
    GrlOperationOptions *options;
    GrlCaps *caps;
    first = FALSE;
    g_debug ("Browsing source: %s", grl_source_get_name (source));


    caps = grl_source_get_caps (source, GRL_OP_BROWSE);
    options = grl_operation_options_new (caps);
    grl_operation_options_set_count (options, 5);
    grl_operation_options_set_flags (options, GRL_RESOLVE_IDLE_RELAY);

    grl_source_browse (source,
                       NULL,
                       keys,
                       options,
                       browse_cb,
                       NULL);
    g_object_unref (caps);
    g_object_unref (options);
  }

  g_list_free (keys);
}
