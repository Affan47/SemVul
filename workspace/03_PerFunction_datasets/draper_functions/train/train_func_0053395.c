glade_base_editor_get_child_selected (GladeBaseEditor *e, GtkTreeIter *iter)
{
  GtkTreeSelection *sel =
    gtk_tree_view_get_selection (GTK_TREE_VIEW (e->priv->treeview));
  return (sel) ? gtk_tree_selection_get_selected (sel, NULL, iter) : FALSE;
}
