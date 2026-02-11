test_roundtrip (void)
{
  int i;
  gchar *uri, *hostname, *res;
  GError *error;

  for (i = 0; i < G_N_ELEMENTS (to_uri_tests); i++)
    {
      error = NULL;
      uri = g_filename_to_uri (to_uri_tests[i].filename,
			       to_uri_tests[i].hostname,
			       &error);

      cut_assert (!error);

      error = NULL;
      res = g_filename_from_uri (uri, &hostname, &error);
      cut_assert (!error);

      cut_assert_equal_string (to_uri_tests[i].filename, res);

      if (!to_uri_tests[i].hostname)
        to_uri_tests[i].hostname = "";
      if (!hostname)
        hostname = "";
      cut_assert_equal_string (to_uri_tests[i].hostname, hostname);
    }
}
