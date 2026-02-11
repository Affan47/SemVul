totem_subtitle_encoding_set (GtkComboBox * combo, const char *encoding)
{
  GtkTreeModel *model;
  GtkTreeIter iter, iter2;
  gint index_, i;

  g_return_if_fail (encoding != NULL);

  model = gtk_combo_box_get_model (combo);
  index_ = subtitle_encoding_get_index (encoding);
  gtk_tree_model_get_iter_first (model, &iter);
  do {
    if (!gtk_tree_model_iter_has_child (model, &iter))
      continue;
    if (!gtk_tree_model_iter_children (model, &iter2, &iter))
      continue;
    do {
      gtk_tree_model_get (model, &iter2, INDEX_COL, &i, -1);
      if (i == index_)
        break;
    } while (gtk_tree_model_iter_next (model, &iter2));
    if (i == index_)
      break;
  } while (gtk_tree_model_iter_next (model, &iter));
  gtk_combo_box_set_active_iter (combo, &iter2);
}
