popup_menu_remove_from_memory (GtkMenuItem *menuitem,
                               GtrTranslationMemoryUi *tm_ui)
{
  GtkTreeSelection *selection;
  GtkTreeModel *model;
  GtkTreeIter iter;
  gint level;
  const gchar *original;
  gchar *translation;

  selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (tm_ui->priv->tree_view));
  if (!selection || !gtk_tree_selection_get_selected (selection, &model, &iter))
    return;

  gtk_tree_model_get (model, &iter,
                      LEVEL_COLUMN, &level,
                      -1);

  if (level != 100)
    return;

  gtk_tree_model_get (model, &iter,
                      STRING_COLUMN, &translation,
                      -1);

  original = gtr_msg_get_msgid (tm_ui->priv->msg);
  gtr_translation_memory_remove (tm_ui->priv->translation_memory, original, translation);

  g_free (translation);


  showed_message_cb (tm_ui->priv->tab, tm_ui->priv->msg, tm_ui);
}
