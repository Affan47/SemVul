get_codepoint_list (GucharmapChaptersModel *chapters,
                    GtkTreeIter *iter)
{
  GtkTreeModel *model = GTK_TREE_MODEL (chapters);
  UnicodeBlock *unicode_block;

  gtk_tree_model_get (model, iter, BLOCK_CHAPTERS_MODEL_UNICODE_BLOCK_PTR, &unicode_block, -1);


  if (unicode_block == NULL)
    return gucharmap_block_codepoint_list_new (0, UNICHAR_MAX);

  return gucharmap_block_codepoint_list_new (unicode_block->start, unicode_block->end);
}
