error_message (CcDisplayPanel *self, const char *primary_text, const char *secondary_text)
{
  GtkWidget *toplevel;
  GtkWidget *dialog;

  if (self && self->priv->panel)
    toplevel = gtk_widget_get_toplevel (self->priv->panel);
  else
    toplevel = NULL;

  dialog = gtk_message_dialog_new (GTK_WINDOW (toplevel),
                                   GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                   GTK_MESSAGE_ERROR,
                                   GTK_BUTTONS_CLOSE,
                                   "%s", primary_text);

  if (secondary_text)
    gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "%s", secondary_text);

  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}
