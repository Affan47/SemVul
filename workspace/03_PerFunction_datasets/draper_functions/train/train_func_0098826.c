gnac_playlist_is_mime_playlist(const gchar *mime)
{
  if (!mime) return FALSE;

  guint i;
  for (i = 0; mime_playlist[i].mime; i++) {
    if (g_ascii_strcasecmp(mime, mime_playlist[i].mime) == 0) {
      return TRUE;
    }
  }

  return FALSE;
}
