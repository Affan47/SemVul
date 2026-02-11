test_episodes (void)
{
  GrlRegistry *registry;
  GrlSource *source;
  guint i;

  struct {
    char *title;
    char *show;
    int season;
    int episode;
  } episode_tests[] = {
    { "The.Slap.S01E01.Hector.WS.PDTV.XviD-BWB.avi", "The Slap", 1, 1 },
    { "metalocalypse.s02e01.dvdrip.xvid-ffndvd.avi", "metalocalypse", 2, 1 },
    { "Boardwalk.Empire.S04E01.HDTV.x264-2HD.mp4", "Boardwalk Empire", 4, 1 },
  };


  registry = grl_registry_get_default ();
  source = grl_registry_lookup_source (registry, "grl-local-metadata");
  g_assert (source);

  for (i = 0; i < G_N_ELEMENTS(episode_tests); i++) {
    char *show;
    int season, episode;

    show = get_show_for_title (source, episode_tests[i].title, &season, &episode);
    g_assert_cmpstr (episode_tests[i].show, ==, show);
    if (show != NULL) {
      g_assert_cmpint (episode_tests[i].season, ==, season);
      g_assert_cmpint (episode_tests[i].episode, ==, episode);
    }
    g_free (show);
  }
}
