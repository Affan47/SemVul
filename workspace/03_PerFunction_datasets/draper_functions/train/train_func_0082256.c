tree_view_button_release_event_cb (GtkWidget      *widget,
                                   GdkEventButton *event,
                                   gpointer       *user_data)
{
  GoaPanelAddAccountDialog *add_account = GOA_PANEL_ADD_ACCOUNT_DIALOG (user_data);
  GoaPanelAddAccountDialogPrivate *priv = add_account->priv;
  GtkTreePath *path;
  GtkTreeViewColumn *column;

  if (event->button != 1 || priv->ignore_release)
    return TRUE;

  gtk_tree_view_get_cursor (GTK_TREE_VIEW (widget), &path, &column);
  if (path == NULL)
    return TRUE;

  gtk_tree_view_row_activated (GTK_TREE_VIEW (widget), path, column);
  gtk_tree_path_free (path);

  return TRUE;
}
