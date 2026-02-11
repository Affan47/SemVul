gt_language_view_source_changed_h (GtkTreeSelection *selection,
				   gpointer user_data)
{
  GtkTreeView *source_view = gtk_tree_selection_get_tree_view(selection);
  GtkTreeView *dest_view = user_data;
  GtkTreeModel *model;
  GtkTreeIter iter;
  GtkListStore *dest_store = NULL;
  char *from = NULL;
  char *to;

  if (gtk_tree_selection_get_selected(selection, &model, &iter))
    gtk_tree_model_get(model, &iter,
		       COLUMN_TAG, &from,
		       SOURCE_COLUMN_DEST_STORE, &dest_store,
		       -1);

  gt_language_view_set_conf_selected_tag(source_view, from);
  g_free(from);

  to = gt_language_view_get_conf_selected_tag(dest_view);

  gtk_tree_view_set_model(dest_view, (GtkTreeModel *) dest_store);
  if (dest_store)
    g_object_unref(dest_store);

  gtk_tree_view_set_search_column(dest_view, COLUMN_NAME);

  gt_language_view_select(dest_view, to);
  g_free(to);
}
