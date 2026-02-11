account_clicked_cb (G_GNUC_UNUSED GtkWidget *w,
		    GdkEventButton *event,
		    gpointer data)
{
  AccountsWindow *self = ACCOUNTS_WINDOW (data);

  GtkTreePath *path = NULL;
  GtkTreeView *tree_view = NULL;
  GtkTreeModel *model = NULL;
  GtkTreeIter iter;

  Ekiga::Account *account = NULL;

  tree_view = GTK_TREE_VIEW (self->priv->accounts_list);
  model = gtk_tree_view_get_model (tree_view);

  if (event->type == GDK_BUTTON_PRESS || event->type == GDK_KEY_PRESS || event->type == GDK_2BUTTON_PRESS) {

    if (gtk_tree_view_get_path_at_pos (GTK_TREE_VIEW (tree_view),
                                       (gint) event->x, (gint) event->y,
                                       &path, NULL, NULL, NULL)) {

      if (gtk_tree_model_get_iter (model, &iter, path)) {

        gtk_tree_model_get (model, &iter,
                            COLUMN_ACCOUNT, &account,
                            -1);

        gtk_tree_path_free (path);
      }
    }
  }

  if (account == NULL)
    return FALSE;

  if (event->type == GDK_BUTTON_PRESS || event->type == GDK_KEY_PRESS) {

    populate_menu (GTK_WIDGET (data));

    if (event->button == 3) {

      MenuBuilderGtk builder;
      account->populate_menu (builder);
      if (!builder.empty ()) {

        gtk_widget_show_all (builder.menu);
        gtk_menu_popup (GTK_MENU (builder.menu), NULL, NULL,
                        NULL, NULL, event->button, event->time);
        g_signal_connect (builder.menu, "hide",
                          G_CALLBACK (g_object_unref),
                          (gpointer) builder.menu);
      }
      g_object_ref_sink (G_OBJECT (builder.menu));
    }
  }
  else if (event->type == GDK_2BUTTON_PRESS) {

    Ekiga::TriggerMenuBuilder builder;
    account->populate_menu (builder);
  }

  return TRUE;
}
