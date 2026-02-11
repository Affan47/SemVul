collect_expected_matches (va_list args)
{


  while (TRUE)
    {
      Match *match;
      const gchar *expected_string = va_arg (args, const gchar *);
      if (expected_string == NULL)
        break;
      match = g_new0 (Match, 1);
      match->string = g_strdup (expected_string);
      match->start = va_arg (args, gint);
      match->end = va_arg (args, gint);
      expected_matches = g_slist_prepend (expected_matches, match);
    }
  expected_matches = g_slist_reverse (expected_matches);
}
