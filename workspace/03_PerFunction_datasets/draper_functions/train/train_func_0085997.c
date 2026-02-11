markup_dir_list_available_local_descs (MarkupDir *dir)
{
#define LOCALE_FILE_PREFIX "%gconf-tree-"
#define LOCALE_FILE_SUFFIX ".xml"
#define LOCALE_FILE_PREFIX_LEN (sizeof (LOCALE_FILE_PREFIX) - 1)
#define LOCALE_FILE_SUFFIX_LEN (sizeof (LOCALE_FILE_SUFFIX) - 1)

  GDir       *dp;
  char       *dir_path;
  const char *dent;

  dir_path = markup_dir_build_dir_path (dir, TRUE);

  if ((dp = g_dir_open (dir_path, 0, NULL)) == NULL)
    {


      gconf_log (GCL_DEBUG,
                 "Could not open directory \"%s\": %s\n",
                 dir_path, g_strerror (errno));
      g_free (dir_path);
      return;
    }

  g_assert (dir->available_local_descs != NULL);
  g_assert (g_hash_table_size (dir->available_local_descs) == 0);

  while ((dent = g_dir_read_name (dp)) != NULL)
    {
      gsize  dent_len;
      char  *locale;

      dent_len = strlen (dent);

      if (dent_len <= LOCALE_FILE_PREFIX_LEN + LOCALE_FILE_SUFFIX_LEN)
        continue;

      if (strncmp (dent, LOCALE_FILE_PREFIX, LOCALE_FILE_PREFIX_LEN) != 0)
        continue;

      if (strcmp (dent + dent_len - LOCALE_FILE_SUFFIX_LEN, LOCALE_FILE_SUFFIX) != 0)
        continue;

      locale = g_strndup (dent + LOCALE_FILE_PREFIX_LEN,
                          dent_len - LOCALE_FILE_PREFIX_LEN - LOCALE_FILE_SUFFIX_LEN);

      g_hash_table_replace (dir->available_local_descs,
                            locale,
                            GINT_TO_POINTER (FALSE));
    }

  if (g_hash_table_size (dir->available_local_descs) != 0)
    dir->all_local_descs_loaded = FALSE;


  g_dir_close (dp);

  g_free (dir_path);

#undef LOCALE_FILE_SUFFIX_LEN
#undef LOCALE_FILE_PREFIX_LEN
#undef LOCALE_FILE_SUFFIX
#undef LOCALE_FILE_PREFIX
}
