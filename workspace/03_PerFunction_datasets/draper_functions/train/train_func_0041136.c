test_missing_configuration (void)
{
  GrlMedia *media = NULL;
  GrlOperationOptions *options = NULL;
  GError *error = NULL;

  test_setup_tmdb ();


  media = grl_media_video_new ();
  g_assert (media != NULL);
  grl_media_set_title (media, "Non-Empty");

  GrlSource *source = test_get_source();
  g_assert (source);
  options = grl_operation_options_new (NULL);
  g_assert (options != NULL);
  grl_source_resolve_sync (source,
                           media,
                           grl_source_supported_keys (source),
                           options,
                           &error);


  g_assert (error != NULL);

  g_clear_object (&media);
  g_clear_object (&options);
  g_clear_error (&error);

  test_shutdown_tmdb ();
}
