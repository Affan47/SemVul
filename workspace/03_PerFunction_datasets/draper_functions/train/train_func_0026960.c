gui_get_iter_by_id(GtkTreeIter *iter, gint id) {
  GtkTreeModel *tm = GTK_TREE_MODEL(glurp->gui_playlist);
  gint cid;

  if( !gtk_tree_model_get_iter_first(tm, iter) ) {
    debug("Couldn't get first iter");
    return FALSE;
  }

  do {
    gtk_tree_model_get(tm, iter, PL_ID, &cid, -1);
    if( cid == id ) return TRUE;
  } while( gtk_tree_model_iter_next(tm, iter) );

  return FALSE;
}
