export_playlist_file_response(GtkDialog *fc, gint response, struct fcd *fcd) {

    switch (response) {
    case RESPONSE_APPLY:
        export_playlist_file_retrieve_options(fcd, GTK_FILE_CHOOSER(fc));
        break;
    case GTK_RESPONSE_ACCEPT:
        export_playlist_file_retrieve_options(fcd, GTK_FILE_CHOOSER(fc));
        fcd->filename = g_strdup(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fc)));
        gdk_threads_add_idle((GSourceFunc) export_playlist_file_write_cb, fcd);
        gtk_widget_destroy(GTK_WIDGET (fc));
        break;
    case GTK_RESPONSE_CANCEL:
        export_fcd_cleanup(fcd);
        gtk_widget_destroy(GTK_WIDGET (fc));
        break;
    case GTK_RESPONSE_DELETE_EVENT:
        export_fcd_cleanup(fcd);
        break;
    default:
        fprintf(stderr, "Programming error: export_playlist_file_response(): unknown response '%d'\n", response);
        break;
    }
}
