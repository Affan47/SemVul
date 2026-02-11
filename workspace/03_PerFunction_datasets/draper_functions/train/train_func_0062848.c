gtr_dict_panel_create_warning_dialog (const gchar * primary,
                                      const gchar * secondary)
{
  GtkWidget *dialog;

  if (!primary)
    return;

  dialog = gtk_message_dialog_new (NULL,
                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                   GTK_MESSAGE_WARNING,
                                   GTK_BUTTONS_CLOSE, "%s", primary);

  if (secondary)
    gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
                                              "%s", secondary);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}
