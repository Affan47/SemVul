launch_process (char **argv, GtkWindow *parent)
{
        GError *error;
        GtkWidget *dialog;

        error = NULL;
        if (!g_spawn_async (NULL,
                            argv, NULL,
                            0,
                            NULL, NULL,
                            NULL,
                            &error)) {


                dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING,
						 GTK_BUTTONS_OK, _("Unable to launch the Personal File Sharing Preferences"));

                gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "%s", error->message);

                gtk_dialog_run (GTK_DIALOG (dialog));
                gtk_widget_destroy (dialog);

                g_error_free (error);
        }
}
