on_ui_add_row_activated(GtkTreeView *tv, GtkTreePath *path, GtkTreeViewColumn *col, gpointer user_data) {
  GtkTreeModel *tm = gtk_tree_view_get_model( tv );
  GtkTreeIter iter;

  if (!tm) {
    debug("Couldn't get the tree model for add tree");
    return;
  }

  if (!gtk_tree_model_get_iter(tm, &iter, path)) {
    debug("couldn't get a valid iter for the activated row (!)");
    return;
  }

  if( gtk_tree_model_iter_n_children(tm, &iter) > 0 ) {

    debug("A directory is activated in the add window");
    if ( gtk_tree_view_row_expanded(tv, path) ) {
      gtk_tree_view_collapse_row(tv, path);
    } else {
      gtk_tree_view_expand_row(tv, path, FALSE);
    }
  } else {


    debug("A song is activated in the add window");
    gui_load_song(tm, iter);
  }
}
