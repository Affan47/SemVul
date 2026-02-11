gucharmap_chapters_view_get_selected (GucharmapChaptersView *view)
{
  GtkTreeView *tree_view = GTK_TREE_VIEW (view);
  GtkTreeSelection *selection = gtk_tree_view_get_selection (tree_view);
  GtkTreeModel *model;
  GtkTreeIter iter;
  gchar *name = NULL;

  if (gtk_tree_selection_get_selected (selection, &model, &iter))
    gtk_tree_model_get(model, &iter, GUCHARMAP_CHAPTERS_MODEL_COLUMN_ID, &name, -1);

  return name;
}
