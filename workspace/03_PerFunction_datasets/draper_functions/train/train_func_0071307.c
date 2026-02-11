choose_file_with_preview(const gchar *title, GtkWidget *parent)
{
        GtkWidget *chooser, *preview;
        gchar *filename;

        chooser = gtk_file_chooser_dialog_new(title, GTK_WINDOW(parent),
                         GTK_FILE_CHOOSER_ACTION_OPEN,
                         GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                         GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
        gtk_dialog_set_default_response(GTK_DIALOG(chooser), GTK_RESPONSE_ACCEPT);
        gtk_file_chooser_set_local_only(GTK_FILE_CHOOSER(chooser), TRUE);
        gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(chooser), FALSE);
        gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(chooser), TRUE);
        gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(chooser), g_get_home_dir());

        preview = gtk_image_new();
        gtk_widget_set_size_request(preview, MAX_PREVIEWSIZE, MAX_PREVIEWSIZE);
        gtk_file_chooser_set_preview_widget(GTK_FILE_CHOOSER(chooser), preview);
        gtk_file_chooser_set_preview_widget_active(GTK_FILE_CHOOSER(chooser), FALSE);
        g_signal_connect(chooser, "update-preview",
                         G_CALLBACK(chooser_update_preview), preview);

        gtk_widget_show_all(chooser);
        filename = NULL;
        switch (gtk_dialog_run(GTK_DIALOG(chooser))) {
        case GTK_RESPONSE_ACCEPT:
                filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser));
                break;
        default:
                break;
        }
        gtk_widget_destroy(chooser);

        return filename;
}
