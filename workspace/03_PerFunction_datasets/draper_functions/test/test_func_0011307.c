populate_stream_liststore() {
  GlurpStream *s = NULL;
  GtkTreeIter iter;

  gtk_list_store_clear(glurp->gui_stream_list);

  for( s = glurp->stream_history; s; s = s->next ) {
    debug("Adding row '%s'", s->url);
    gtk_list_store_append(glurp->gui_stream_list, &iter);
    gtk_list_store_set(glurp->gui_stream_list, &iter, 0, g_strdup(s->url), -1);
  }

  statusbar_print("Stream combobox model populated");

}
