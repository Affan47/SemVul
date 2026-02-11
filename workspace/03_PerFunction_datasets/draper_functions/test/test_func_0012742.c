gucharmap_block_chapters_model_init (GucharmapBlockChaptersModel *model)
{
  GtkListStore *store = GTK_LIST_STORE (model);
  GtkTreeIter iter;
  guint i;
  GType types[] = {
    G_TYPE_STRING,
    G_TYPE_STRING,
    G_TYPE_POINTER
  };

  gtk_list_store_set_column_types (store, G_N_ELEMENTS (types), types);

  gtk_list_store_append (store, &iter);
  gtk_list_store_set (store, &iter,
                      BLOCK_CHAPTERS_MODEL_ID, "All",
                      BLOCK_CHAPTERS_MODEL_LABEL, _("All"),
                      BLOCK_CHAPTERS_MODEL_UNICODE_BLOCK_PTR, NULL,
                      -1);

  for (i = 0;  i < G_N_ELEMENTS (unicode_blocks); i++)
    {
      const char *block_name;

      block_name = unicode_blocks_strings + unicode_blocks[i].block_name_index;

      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter,
                          BLOCK_CHAPTERS_MODEL_ID, block_name,
                          BLOCK_CHAPTERS_MODEL_LABEL, _(block_name),
                          BLOCK_CHAPTERS_MODEL_UNICODE_BLOCK_PTR, unicode_blocks + i,
                          -1);
    }

  gtk_tree_sortable_set_sort_func (GTK_TREE_SORTABLE (model),
                                   GUCHARMAP_CHAPTERS_MODEL_COLUMN_LABEL,
                                   (GtkTreeIterCompareFunc) compare_iters,
                                   NULL, NULL);
}
