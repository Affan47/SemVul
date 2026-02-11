add_account_dialog_get_provider (GoaPanelAddAccountDialog *add_account)
{
  GoaPanelAddAccountDialogPrivate *priv = add_account->priv;
  GoaProvider *provider;
  GtkTreeIter iter;

  if (priv->path == NULL)
    return NULL;

  if (!gtk_tree_model_get_iter (GTK_TREE_MODEL (priv->list_store), &iter, priv->path))
    return NULL;

  gtk_tree_model_get (GTK_TREE_MODEL (priv->list_store), &iter, COLUMN_PROVIDER, &provider, -1);
  return provider;
}
