mpdclient_get_current_song(void) {
  song *s;
  struct mpd_song *ms;
  const char *uri;
  gchar *song_file;

  mpdclient_connect();
  if ( (ms = (*gjmpd_run_current_song)(gjay->mpdclient_connection)) == NULL)
    return NULL;
  uri = (*gjmpd_song_get_uri)(ms);
  song_file = g_strdup_printf("%s/%s",gjay->prefs->song_root_dir,uri);

  s = g_hash_table_lookup(gjay->song_name_hash, song_file);
  (*gjmpd_song_free)(ms);
  g_free(song_file);
  return s;
}
