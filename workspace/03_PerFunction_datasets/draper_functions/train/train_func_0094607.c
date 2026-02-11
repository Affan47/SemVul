magnatune_download_callback(const GEADAsyncHandler *handle, const GEADStatus status, gpointer user_data)
{
    GtkWidget *pb = user_data;
    const gchar *uri = gmpc_easy_handler_get_uri(handle);
    if(status == GEAD_DONE)
    {
        goffset length;
        const char *data = gmpc_easy_handler_get_data(handle, &length);

        magnatune_db_load_data(data, length);
        if(length <= 0 || data == NULL) {
            playlist3_show_error_message("Failed to download magnatune db: size is 0.",ERROR_WARNING);
        }
        gtk_widget_hide(gtk_widget_get_parent(pb));
        magnatune_get_genre_list();
        downloading = FALSE;
    }
    else if (status == GEAD_CANCELLED)
    {
        gtk_widget_hide(gtk_widget_get_parent(pb));
        magnatune_get_genre_list();
        downloading = FALSE;
    }
    else if (status == GEAD_PROGRESS)
    {
        goffset length;
        goffset total = gmpc_easy_handler_get_content_size(handle);

        gmpc_easy_handler_get_data(handle, &length);
        if(total > 0)
        {
            double fraction = (100*length)/(total);
            gchar *size = g_format_size_for_display((goffset)length);
            gchar *strtotal = g_format_size_for_display((goffset)total);
            gchar *label = g_strdup_printf("Downloading music catalog (%s of %s done)",size,strtotal);
            g_free(strtotal);
            g_free(size);
            gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pb), label);
            g_free(label);
            gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pb),fraction/100.0);
        }
        else
        {
            gtk_progress_bar_pulse(GTK_PROGRESS_BAR(pb));
        }
    }
}
