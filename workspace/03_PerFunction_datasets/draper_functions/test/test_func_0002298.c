openIsoCbk(GtkMenuItem* menuItem, gpointer data)
{
    GtkWidget *dialog;
    char* filename = NULL;
    GtkFileFilter* nameFilter;
    int dialogRespose;

    dialog = gtk_file_chooser_dialog_new("Open File",
                                         NULL,
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                         GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                         NULL);

    nameFilter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(GTK_FILE_FILTER(nameFilter), "*.[iI][sS][oO]");
    gtk_file_filter_set_name(GTK_FILE_FILTER(nameFilter), _("ISO Images"));
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), GTK_FILE_FILTER(nameFilter));

    nameFilter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(GTK_FILE_FILTER(nameFilter), "*.[nN][rR][gG]");
    gtk_file_filter_set_name(GTK_FILE_FILTER(nameFilter), _("NRG Images"));
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), GTK_FILE_FILTER(nameFilter));

    nameFilter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(GTK_FILE_FILTER(nameFilter), "*.[mM][dD][fF]");
    gtk_file_filter_set_name(GTK_FILE_FILTER(nameFilter), _("MDF Images"));
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), GTK_FILE_FILTER(nameFilter));

    nameFilter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(GTK_FILE_FILTER(nameFilter), "*");
    gtk_file_filter_set_name(GTK_FILE_FILTER(nameFilter), _("All files"));
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), GTK_FILE_FILTER(nameFilter));

    if(GBLappSettings.lastIsoDir != NULL)
        gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), GBLappSettings.lastIsoDir);

    dialogRespose = gtk_dialog_run(GTK_DIALOG(dialog));

    if(dialogRespose == GTK_RESPONSE_ACCEPT)
    {
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));


        char* lastIsoDir = gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(dialog));
        if(lastIsoDir)
        {
            if(GBLappSettings.lastIsoDir != NULL && strlen(lastIsoDir) > strlen(GBLappSettings.lastIsoDir))
            {
                free(GBLappSettings.lastIsoDir);
                GBLappSettings.lastIsoDir = NULL;
            }

            if(GBLappSettings.lastIsoDir == NULL)
                GBLappSettings.lastIsoDir = malloc(strlen(lastIsoDir) + 1);

            strcpy(GBLappSettings.lastIsoDir, lastIsoDir);

            g_free(lastIsoDir);
        }
        else
        {
            free(GBLappSettings.lastIsoDir);
            GBLappSettings.lastIsoDir = NULL;
        }

    }

    gtk_widget_destroy(dialog);

    if(dialogRespose == GTK_RESPONSE_ACCEPT)
    {
        openIso(filename);

        g_free(filename);
    }


    return TRUE;
}
