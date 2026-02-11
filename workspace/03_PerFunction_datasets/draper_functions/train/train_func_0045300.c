subtitle_encoding_create_store (void)
{
  gchar *label;
  const gchar *lastlang = "";
  GtkTreeIter iter, iter2;
  GtkTreeStore *store;
  int i;

  store = gtk_tree_store_new (2, G_TYPE_INT, G_TYPE_STRING);

  for (i = 0; i < SUBTITLE_ENCODING_LAST; i++) {
    if (strcmp (lastlang, encodings[i].name)) {
      lastlang = encodings[i].name;
      gtk_tree_store_append (store, &iter, NULL);
      gtk_tree_store_set (store, &iter, INDEX_COL,
          -1, NAME_COL, lastlang, -1);
    }
    label = g_strdup_printf("%s (%s)", lastlang, encodings[i].charset);
    gtk_tree_store_append (store, &iter2, &iter);
    gtk_tree_store_set (store, &iter2, INDEX_COL,
        encodings[i].index, NAME_COL, label, -1);
    g_free(label);
  }
  gtk_tree_sortable_set_default_sort_func (GTK_TREE_SORTABLE (store),
      compare, NULL, NULL);
  gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (store),
      NAME_COL, GTK_SORT_ASCENDING);
  return GTK_TREE_MODEL (store);
}
