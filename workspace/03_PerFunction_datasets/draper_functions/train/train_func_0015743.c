audgui_jump_to_time (void)
{
    if (window)
        gtk_widget_destroy (window);

    window = gtk_dialog_new_with_buttons (_("Jump to Time"), NULL, 0,
     GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, GTK_STOCK_JUMP_TO,
     GTK_RESPONSE_ACCEPT, NULL);
    gtk_widget_set_size_request (window, 200, -1);
    gtk_window_set_resizable ((GtkWindow *) window, FALSE);
    gtk_dialog_set_default_response ((GtkDialog *) window, GTK_RESPONSE_ACCEPT);

    GtkWidget * box = gtk_dialog_get_content_area ((GtkDialog *) window);

    GtkWidget * label = gtk_label_new (_("Enter time (minutes:seconds):"));
    gtk_misc_set_alignment ((GtkMisc *) label, 0, 0);
    gtk_box_pack_start ((GtkBox *) box, label, FALSE, FALSE, 0);

    GtkWidget * entry = gtk_entry_new ();
    gtk_entry_set_activates_default ((GtkEntry *) entry, TRUE);
    gtk_box_pack_start ((GtkBox *) box, entry, FALSE, FALSE, 0);

    if (aud_drct_get_playing ())
    {
        char buf[16];
        int time = aud_drct_get_time () / 1000;
        snprintf (buf, sizeof buf, "%u:%02u", time / 60, time % 60);
        gtk_entry_set_text ((GtkEntry *) entry, buf);
    }

    g_object_set_data ((GObject *) window, "entry", entry);

    g_signal_connect (window, "response", (GCallback) response_cb, NULL);
    g_signal_connect (window, "destroy", (GCallback) gtk_widget_destroyed, & window);

    gtk_widget_show_all (window);
}
