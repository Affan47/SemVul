parse_debug_list (const gchar * list)
{
  gchar **split;
  gchar **walk;

  g_assert (list);

  split = g_strsplit (list, ",", 0);

  for (walk = split; *walk; walk++) {
    if (strchr (*walk, ':')) {
      gchar **values = g_strsplit (*walk, ":", 2);

      if (values[0] && values[1]) {
        GstDebugLevel level;
        const gchar *category;

        if (parse_debug_category (values[0], &category)
            && parse_debug_level (values[1], &level))
          gst_debug_set_threshold_for_name (category, level);
      }

      g_strfreev (values);
    } else {
      GstDebugLevel level;

      if (parse_debug_level (*walk, &level))
        gst_debug_set_default_threshold (level);
    }
  }

  g_strfreev (split);
}
