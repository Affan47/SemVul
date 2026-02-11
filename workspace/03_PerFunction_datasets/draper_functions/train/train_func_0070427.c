ario_playlist_cmd_save (GtkAction *action,
                        ArioPlaylist *playlist)
{
        ARIO_LOG_FUNCTION_START;
        GtkWidget *dialog;
        GtkWidget *hbox;
        GtkWidget *label, *entry;
        gint retval = GTK_RESPONSE_CANCEL;
        gchar *name;


        dialog = gtk_dialog_new_with_buttons (_("Save playlist"),
                                              NULL,
                                              GTK_DIALOG_DESTROY_WITH_PARENT,
                                              GTK_STOCK_CANCEL,
                                              GTK_RESPONSE_CANCEL,
                                              GTK_STOCK_OK,
                                              GTK_RESPONSE_OK,
                                              NULL);
        gtk_dialog_set_default_response (GTK_DIALOG (dialog),
                                         GTK_RESPONSE_OK);
        label = gtk_label_new (_("Playlist name :"));
        entry = gtk_entry_new ();
        hbox = gtk_hbox_new (FALSE, 5);

        gtk_box_pack_start (GTK_BOX (hbox),
                            label,
                            TRUE, TRUE,
                            0);
        gtk_box_pack_start (GTK_BOX (hbox),
                            entry,
                            TRUE, TRUE,
                            0);
        gtk_container_set_border_width (GTK_CONTAINER (hbox), 10);
        gtk_box_set_spacing (GTK_BOX (hbox), 4);
        gtk_container_add (GTK_CONTAINER (gtk_dialog_get_content_area (GTK_DIALOG (dialog))),
                           hbox);
        gtk_widget_show_all (dialog);


        retval = gtk_dialog_run (GTK_DIALOG(dialog));
        if (retval != GTK_RESPONSE_OK) {
                gtk_widget_destroy (dialog);
                return;
        }


        name = g_strdup (gtk_entry_get_text (GTK_ENTRY (entry)));
        gtk_widget_destroy (dialog);


        if (ario_server_save_playlist (name)) {

                dialog = gtk_message_dialog_new (NULL,
                                                 GTK_DIALOG_MODAL,
                                                 GTK_MESSAGE_QUESTION,
                                                 GTK_BUTTONS_YES_NO,
                                                 _("Playlist already exists. Do you want to overwrite it?"));

                retval = gtk_dialog_run (GTK_DIALOG (dialog));
                gtk_widget_destroy (dialog);
                if (retval == GTK_RESPONSE_YES) {
                        ario_server_delete_playlist (name);
                        ario_server_save_playlist (name);
                }
        }
        g_free (name);
}
