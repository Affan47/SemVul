gnac_playlist_parse(GFile       *file,
                    const gchar *mime)
{
  guint i;
  for (i = 0; mime_playlist[i].mime; i++) {
    if (g_ascii_strcasecmp(mime, mime_playlist[i].mime) == 0) {
      mime_playlist[i].handler(file);
      return;
    }
  }
}
