tree_view_popup_clear_handler (GtkMenuItem        *item,
                               GgdDoctypeSelector *selector)
{
  GtkTreeIter       iter;
  GtkTreeSelection *selection;

  selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (selector->priv->view));
  if (gtk_tree_selection_get_selected (selection, NULL, &iter)) {
    gtk_list_store_set (selector->priv->store, &iter, COLUMN_DOCTYPE, "", -1);
  }
}
