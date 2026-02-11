show_override_dialog (GtkWindow *parent)
{
  GtkWidget *msg_dialog = (GtkWidget *) NULL;
  gint result = GTK_RESPONSE_NO;

  msg_dialog = gtk_message_dialog_new (GTK_WINDOW (parent),
                                       GTK_DIALOG_MODAL,
                                       GTK_MESSAGE_WARNING,
                                       GTK_BUTTONS_YES_NO,
                                       gettext ("File Exists. Overwrite"));


  result = gtk_dialog_run (GTK_DIALOG (msg_dialog));
    if (msg_dialog)
      {
        gtk_widget_destroy (msg_dialog);
        msg_dialog = NULL;
      }

   return result;
}
