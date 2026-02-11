irc_network_dialog_setup (TpawIrcNetworkDialog *dialog)
{
  gchar *name, *charset;
  GSList *servers, *l;
  GtkListStore *store;

  g_object_get (dialog->network,
      "name", &name,
      "charset", &charset,
      NULL);
  gtk_entry_set_text (GTK_ENTRY (dialog->entry_network), name);

  store = GTK_LIST_STORE (gtk_tree_view_get_model (
        GTK_TREE_VIEW (dialog->treeview_servers)));

  servers = tpaw_irc_network_get_servers (dialog->network);
  for (l = servers; l != NULL; l = g_slist_next (l))
    {
      TpawIrcServer *server = l->data;
      GtkTreeIter iter;

      add_server_to_store (store, server, &iter);
    }

  totem_subtitle_encoding_set (GTK_COMBO_BOX (dialog->combobox_charset),
      charset);

  g_slist_foreach (servers, (GFunc) g_object_unref, NULL);
  g_slist_free (servers);
  g_free (name);
  g_free (charset);
}
