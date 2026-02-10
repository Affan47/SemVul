gtk_tree_view_focus(GtkTreeView *view)
{
  GtkTreeModel *model;
  GtkTreePath *path;
  GtkTreeIter iter;

  if ((model = gtk_tree_view_get_model(view))
      && gtk_tree_model_get_iter_first(model, &iter)
      && (path = gtk_tree_model_get_path(model, &iter))) {
    gtk_tree_view_set_cursor(view, path, NULL, FALSE);
    gtk_tree_path_free(path);
    gtk_widget_grab_focus(GTK_WIDGET(view));
  }
}
