get_stream_history(gchar *urls) {
  gchar **streamh = NULL;
  gint i;
  GlurpStream *s = NULL, *os = NULL, *ss = NULL;

  if( !urls || !strlen(urls) ) {
    debug("No stream history");
    return NULL;
  }

  streamh = g_strsplit(urls, " ", 0);

  for( i = 0; streamh[i] && i < MAX_STREAM_HISTORY; i++ ) {
    s = malloc(sizeof(GlurpStream));
    s->url = g_strdup(streamh[i]);
    s->next = NULL;
    if( !i ) ss = s;
    if( os ) os->next = s;
    os = s;
  }

  g_strfreev(streamh);

  return ss;
}
