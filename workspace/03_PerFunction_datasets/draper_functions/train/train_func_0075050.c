on_ui_stream_add_clicked(GtkWidget *widget, gpointer user_data) {
  gchar *url = get_selected_stream();

  if( !url || !g_utf8_strlen(url, -1) ) {
    debug("No stream URL to add, ignoring");

    statusbar_print("No URL to add");

    return FALSE;
  }

  debug("Adding URL: '%s'", url);
  mpd_playlist_add(glurp->mpd, url);
  statusbar_print("URL '%s' added", url);
  push_stream(url);
  populate_stream_liststore();

  return FALSE;
}
