shapers_to_string (void)
{
  GString *shapers = g_string_new (NULL);
  const char **shaper_list = hb_shape_list_shapers ();

  for (; *shaper_list; shaper_list++) {
    g_string_append (shapers, *shaper_list);
    g_string_append_c (shapers, ',');
  }
  g_string_truncate (shapers, MAX (0, (gint)shapers->len - 1));

  return g_string_free (shapers, false);
}
