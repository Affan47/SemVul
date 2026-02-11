REPLACE_DIALOG_init (ReplaceDialog *dialog)
{
  ReplaceDialogPrivate *priv = REPLACE_DIALOG_GET_PRIVATE(dialog);
  priv->diagbox = gtk_dialog_get_content_area (GTK_DIALOG(dialog));

  GtkBuilder *builder = gtk_builder_new ();
  GError *error = NULL;
  guint res = gtk_builder_add_from_file (builder, GPHPEDIT_UI_DIR "/replace_dialog.ui", &error);
  if (!res) {
    g_critical ("Unable to load the UI file!");
    g_error_free(error);
    return ;
  }

  GtkWidget *box = GTK_WIDGET(gtk_builder_get_object (builder, "replace_dialog_content"));
  gtk_widget_show (box);
  gtk_widget_reparent (box, priv->diagbox);

  GtkWidget *table = GTK_WIDGET(gtk_builder_get_object (builder, "table"));
  gtk_table_set_row_spacings (GTK_TABLE (table), 12);

  priv->findentry = gphpedit_history_entry_new ("search-for-entry", TRUE);
	gtk_widget_set_size_request (priv->findentry, 200, -1);
  gtk_widget_show (priv->findentry);
  gtk_table_attach_defaults (GTK_TABLE (table), priv->findentry, 1, 2, 0, 1);


  gchar *buffer;
  buffer = documentable_get_current_selected_text(document_manager_get_current_documentable(main_window.docmg));
  if (buffer) {
      gphpedit_history_entry_prepend_text	(GPHPEDIT_HISTORY_ENTRY(priv->findentry), buffer);
      gtk_combo_box_set_active (GTK_COMBO_BOX(priv->findentry), 0);
  }


  priv->replace_entry = gphpedit_history_entry_new ("replace-with-entry", TRUE);
	gtk_widget_set_size_request (priv->replace_entry, 200, -1);
  gtk_widget_show (priv->replace_entry);
  gtk_table_attach_defaults (GTK_TABLE (table), priv->replace_entry, 1, 2, 1, 2);

  priv->checkcase = GTK_WIDGET(gtk_builder_get_object (builder, "match_case_checkbutton"));
  priv->checkwholeword = GTK_WIDGET(gtk_builder_get_object (builder, "entire_word_checkbutton"));
  priv->checkwholedoc = GTK_WIDGET(gtk_builder_get_object (builder, "checkwholedoc"));
  priv->checkregex = GTK_WIDGET(gtk_builder_get_object (builder, "regexp"));

  priv->close_button = gtk_dialog_add_button (GTK_DIALOG(dialog), GTK_STOCK_CLOSE, GTK_RESPONSE_DELETE_EVENT);
  priv->replaceall_button = gtk_dialog_add_button (GTK_DIALOG(dialog), _("Replace _all"), GTK_RESPONSE_APPLY);
  priv->find_button = gtk_dialog_add_button (GTK_DIALOG(dialog),  GTK_STOCK_FIND_AND_REPLACE, GTK_RESPONSE_OK);

  gtk_dialog_set_default_response (GTK_DIALOG(dialog), GTK_RESPONSE_OK);

  g_signal_connect(G_OBJECT(dialog), "response", G_CALLBACK(replace_dialog_process_response), priv);
}
