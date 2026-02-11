_internal_get_supported_protocols (gpointer data)
{
  const gchar *const *schemes;
  gchar **our_schemes;
  guint num;
  gint i, j;

  schemes = g_vfs_get_supported_uri_schemes (g_vfs_get_default ());
  num = g_strv_length ((gchar **) schemes);

  if (num == 0) {
    GST_WARNING ("No GIO supported URI schemes found");
    return NULL;
  }

  our_schemes = g_new0 (gchar *, num + 1);


  for (i = 0, j = 0; i < num; i++) {
    if (strcmp (schemes[i], "http") == 0 || strcmp (schemes[i], "https") == 0
        || strcmp (schemes[i], "cdda") == 0)
      continue;

    our_schemes[j] = g_strdup (schemes[i]);
    j++;
  }

  return our_schemes;
}
