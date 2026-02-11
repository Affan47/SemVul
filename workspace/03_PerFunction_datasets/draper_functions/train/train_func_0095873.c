test_cancel (void)
{
  GrlOperationOptions *options;
  GrlRegistry *registry;
  GrlSource *source;

  registry = grl_registry_get_default ();
  source = grl_registry_lookup_source (registry, VIMEO_ID);
  g_assert (source);
  options = grl_operation_options_new (NULL);
  grl_operation_options_set_count (options, 2);
  grl_operation_options_set_flags (options, GRL_RESOLVE_FAST_ONLY);
  g_assert (options);

  grl_source_search (source,
                     "gnome",
                     grl_source_supported_keys (source),
                     options,
                     search_cb,
                     NULL);

  if (!main_loop) {
    main_loop = g_main_loop_new (NULL, FALSE);
  }

  g_main_loop_run (main_loop);
  g_object_unref (options);
}
