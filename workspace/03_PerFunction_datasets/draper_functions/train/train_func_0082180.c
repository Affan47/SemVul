get_artist (gchar *dir, gchar *file)
{
  gchar **tmp;
  gchar *artist = NULL;

  if (gnomad_debug != 0) {
    g_print("get_artist()\n");
  }
  tmp = g_strsplit(dir, " - ", 0);


  if (vectorlength(tmp) > 1) {
    artist = g_strdup(*tmp);
    g_strfreev(tmp);
  } else {
    gchar *file2 = kill_tracknumber(file);
    g_strfreev(tmp);
    tmp = g_strsplit(file2, " - ", 0);


    if (vectorlength(tmp) > 2) {
      if (is_a_number(tmp[0])) {
        artist = g_strdup(tmp[1]);
      } else {


        artist = g_strdup(tmp[0]);
      }


    } else if (vectorlength(tmp) > 1) {
      artist = g_strdup(*tmp);
    } else {


      artist = g_strdup(dir);
    }
    g_strfreev(tmp);
    g_free(file2);
  }
  return artist;
}
