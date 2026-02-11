csv_export_custom_entry_cb (GtkWidget *widget, gpointer user_data )
{
    CsvExportInfo *info = user_data;
    const gchar *custom_str;

    GtkAssistant *assistant = GTK_ASSISTANT(info->window);
    gint num = gtk_assistant_get_current_page (assistant);
    GtkWidget *page = gtk_assistant_get_nth_page (assistant, num);

    custom_str = gtk_entry_get_text(GTK_ENTRY(info->custom_entry));
    info->separator_str = strdup(custom_str);

    if (info->use_custom == TRUE && gtk_entry_get_text_length (GTK_ENTRY(info->custom_entry)) == 0)

        gtk_assistant_set_page_complete (assistant, page, FALSE);
    else
        gtk_assistant_set_page_complete (assistant, page, TRUE);
}
