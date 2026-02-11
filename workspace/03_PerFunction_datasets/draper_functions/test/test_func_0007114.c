load_desktop_datafile(gchar *filename)
{
  GKeyFile *keyfile = g_key_file_new ();
  GError *error = NULL;
  if ( ! g_key_file_load_from_file (keyfile,
				    filename,
				    G_KEY_FILE_NONE,
				    &error)  ) {
    if (error)
      g_error ("%s", error->message);
    return;
  }

  gsize n_level;
  gchar **groups = g_key_file_get_groups (keyfile, &n_level);
  int i;
  for (i=0; i<n_level; i++)
    {
      Level level;
      level.level = i + 1;
      level.questions = g_key_file_get_string (keyfile, groups[i],
					      "Questions", NULL);
      level.answers = g_key_file_get_string (keyfile, groups[i],
					    "Answers", NULL);
      g_array_append_vals (levels, &level, 1);
    }

  g_strfreev(groups);
  gcomprisBoard->maxlevel = n_level;
}
