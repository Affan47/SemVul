on_entry_changed (GtkEditable *editable,
                  gpointer     user_data)
{
  IdentifyData *data = user_data;
  gboolean sensitive;

  g_free (data->oauth_verifier);
  data->oauth_verifier = g_strdup (gtk_entry_get_text (GTK_ENTRY (editable)));
  sensitive = data->oauth_verifier != NULL && (strlen (data->oauth_verifier) > 0);
  gtk_dialog_set_response_sensitive (data->dialog, GTK_RESPONSE_OK, sensitive);
}
