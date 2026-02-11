run_dialog (ChangePassphraseData *data)
{
  gint response;

  gtk_widget_show_all (data->dialog);
  response = gtk_dialog_run (GTK_DIALOG (data->dialog));
  gtk_widget_hide (data->dialog);
  if (response == GTK_RESPONSE_OK)
    {
      udisks_encrypted_call_change_passphrase (data->encrypted,
                                               gtk_entry_get_text (GTK_ENTRY (data->existing_passphrase_entry)),
                                               gtk_entry_get_text (GTK_ENTRY (data->passphrase_entry)),
                                               g_variant_new ("a{sv}", NULL),
                                               NULL,
                                               change_passphrase_cb,
                                               data);
    }
  else
    {
      change_passphrase_data_free (data);
    }
}
