add_playlist_to_gui_list(GlurpPl *pl) {
  GtkTreeIter iter;

  if( !glurp->gui_playlist_list ) {
    debug("No playlist list liststore!");
    return;
  }

  if( !pl ) {
    debug("pl == NULL, ignoring");
    return;
  }

  gtk_list_store_append(glurp->gui_playlist_list, &iter);

  gtk_list_store_set(glurp->gui_playlist_list, &iter, 0, pl->name, -1);
}
