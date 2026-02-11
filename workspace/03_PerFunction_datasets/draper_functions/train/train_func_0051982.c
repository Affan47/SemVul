on_selection_changed (GtkTreeSelection* ,
		      gpointer data)
{
  GtkTreeSelection* selection = NULL;
  GtkTreeModel *model = NULL;
  GtkTreeIter iter;
  Ekiga::Account* account = NULL;

  g_return_if_fail (data != NULL);
  AccountsWindow *self = ACCOUNTS_WINDOW (data);

  selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (self->priv->accounts_list));

  if (gtk_tree_selection_get_selected (selection, &model, &iter)) {

    gtk_tree_model_get (model, &iter,
			COLUMN_ACCOUNT, &account,
			-1);
    if (account) {

      self->priv->toolbar.reset ();
      account->populate_menu (self->priv->toolbar);
    } else {

      self->priv->toolbar.reset ();
    }

  } else {

    self->priv->toolbar.reset ();
  }
}
