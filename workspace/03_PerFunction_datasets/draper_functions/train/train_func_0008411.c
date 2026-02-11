initialize_column_titles (GtkTreeView * treeview)
{
  GtkTreeViewColumn *col;
  GList *collist, *node;
  GtkWidget *label;
  int i;

  collist = gtk_tree_view_get_columns (treeview);
  i = 0;
  for (node = collist; node != NULL; node = g_list_next (node)) {
    col = GTK_TREE_VIEW_COLUMN (node->data);
    label = gtk_tree_view_column_get_widget (col);
    if (!label)
      continue;

    gtk_tree_view_column_set_visible (col, i < NumberOfPlayers);
    gtk_label_set_text (GTK_LABEL (label), players[i].name);
    i++;
  }
  g_list_free (collist);
}
