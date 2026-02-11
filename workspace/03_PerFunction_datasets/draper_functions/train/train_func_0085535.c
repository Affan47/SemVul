ario_connection_widget_open_cb (GtkWidget *widget,
                                ArioConnectionWidget *connection_widget)
{
        ARIO_LOG_FUNCTION_START;
        GtkWidget *dialog;


        dialog = gtk_file_chooser_dialog_new (NULL,
                                              NULL,
                                              GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
                                              GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                              GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                              NULL);

        if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
                char *filename;

                filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
                if (filename) {

                        gtk_entry_set_text (GTK_ENTRY (connection_widget->priv->musicdir_entry), filename);
                        g_free (filename);
                }
        }

        gtk_widget_destroy (dialog);
}
