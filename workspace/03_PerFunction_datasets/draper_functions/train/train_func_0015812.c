test_search_normal (void)
{
  GError *error = NULL;
  GList *medias;
  GrlMedia *media;
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

  medias = grl_source_search_sync (source,
                                   "gnome",
                                   grl_source_supported_keys (source),
                                   options,
                                   &error);

  g_assert_cmpint (g_list_length(medias), ==, 2);
  g_assert_no_error (error);

  media = g_list_nth_data (medias, 0);

  g_assert (GRL_IS_MEDIA_VIDEO (media));
  g_assert_cmpstr (grl_media_get_id (media),
                   ==,
                   "31110838");
  g_assert_cmpstr (grl_media_get_title (media),
                   ==,
                   "Mound by Allison Schulnik");
  g_assert_cmpstr (grl_media_get_author (media),
                   ==,
                   "garaco taco");
  g_assert_cmpstr (grl_media_get_thumbnail (media),
                   ==,
                   "http://b.vimeocdn.com/ts/209/404/209404005_100.jpg");

  media = g_list_nth_data (medias, 1);

  g_assert (GRL_IS_MEDIA_VIDEO (media));
  g_assert_cmpstr (grl_media_get_id (media),
                   ==,
                   "13797705");
  g_assert_cmpstr (grl_media_get_title (media),
                   ==,
                   "Shell Yes! motion design mockup");
  g_assert_cmpstr (grl_media_get_author (media),
                   ==,
                   "GNOME Shell");
  g_assert_cmpstr (grl_media_get_thumbnail (media),
                   ==,
                   "http://b.vimeocdn.com/ts/798/198/79819832_100.jpg");

  g_list_free_full (medias, g_object_unref);
  g_object_unref (options);
}
