quick_message (const gchar * const message, gboolean modal)
{

  GtkWidget *dialog;


  dialog =
    gtk_message_dialog_new (NULL, 0, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                            message);

  if (modal)
    gtk_window_set_modal (GTK_WINDOW (dialog), true);

  gtk_dialog_run (GTK_DIALOG (dialog));

  gtk_widget_destroy (dialog);
}
