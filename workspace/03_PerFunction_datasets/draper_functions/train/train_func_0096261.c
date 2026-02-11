terminal_search_dialog_new (GtkWindow   *parent)
{
  GtkWidget *dialog;
  TerminalSearchDialogPrivate *priv;
  GtkListStore *store;
  GtkEntryCompletion *completion;

  priv = g_new0 (TerminalSearchDialogPrivate, 1);

  if (!terminal_util_load_builder_file ("find-dialog.ui",
					"find-dialog", &dialog,
					"search-label", &priv->search_label,
					"search-entry", &priv->search_entry,
					"match-case-checkbutton", &priv->match_case_checkbutton,
					"entire-word-checkbutton", &priv->entire_word_checkbutton,
					"regex-checkbutton", &priv->regex_checkbutton,
					"search-backwards-checkbutton", &priv->backwards_checkbutton,
					"wrap-around-checkbutton", &priv->wrap_around_checkbutton,
					NULL))
  {
    g_free (priv);
    return NULL;
  }

  g_object_set_qdata_full (G_OBJECT (dialog), get_quark (), priv,
			   (GDestroyNotify) terminal_search_dialog_private_destroy);


  priv->search_text_entry = gtk_bin_get_child (GTK_BIN (priv->search_entry));
  gtk_widget_set_size_request (priv->search_entry, 300, -1);

  priv->store = store = gtk_list_store_new (1, G_TYPE_STRING);
  g_object_set (G_OBJECT (priv->search_entry),
		"model", store,
#if GTK_CHECK_VERSION (2, 91, 0)
		"entry-text-column", 0,
#else
		"text-column", 0,
#endif
		NULL);

  priv->completion = completion = gtk_entry_completion_new ();
  gtk_entry_completion_set_model (completion, GTK_TREE_MODEL (store));
  gtk_entry_completion_set_text_column (completion, 0);
  gtk_entry_completion_set_minimum_key_length (completion, HISTORY_MIN_ITEM_LEN);
  gtk_entry_completion_set_popup_completion (completion, FALSE);
  gtk_entry_completion_set_inline_completion (completion, TRUE);
  gtk_entry_set_completion (GTK_ENTRY (priv->search_text_entry), completion);

  gtk_dialog_set_default_response (GTK_DIALOG (dialog), GTK_RESPONSE_ACCEPT);
  gtk_dialog_set_response_sensitive (GTK_DIALOG (dialog), GTK_RESPONSE_ACCEPT, FALSE);

  gtk_entry_set_activates_default (GTK_ENTRY (priv->search_text_entry), TRUE);
  g_signal_connect (priv->search_text_entry, "changed", G_CALLBACK (update_sensitivity), dialog);
  g_signal_connect (priv->regex_checkbutton, "toggled", G_CALLBACK (update_sensitivity), dialog);

  g_signal_connect (dialog, "response", G_CALLBACK (response_handler), NULL);

  if (parent)
    gtk_window_set_transient_for (GTK_WINDOW (dialog), parent);

  return GTK_WIDGET (dialog);
}
