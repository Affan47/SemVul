update_timeout(GtkWidget * label)
{
    gchar *string;
    int entry_length;
    entry_length = strlen(gtk_entry_get_text((GtkEntry *)entry));
    if(entry_length == 0 && timeout_enabled) {
        if (timeout_left > 1){
            timeout_left--;
        } else if (timeout_left == 1) {
            g_io_channel_write_chars(g_stdout, "@GUEST@\n", -1, NULL, NULL);
            g_io_channel_flush(g_stdout, NULL);
            timeout_left = 0;
            timeout_enabled = FALSE;
        } else if (timeout_left == 0){
            timeout_left = login_timeout;
        }
        string = g_strdup_printf(_("Automatic login in %d seconds"), timeout_left);
        gtk_label_set_markup((GtkLabel *) label, string);
        g_free(string);
        gtk_widget_show(timeoutbox);
    } else {
        timeout_left = 0;
        gtk_widget_hide(timeoutbox);
    }
    return TRUE;
}
