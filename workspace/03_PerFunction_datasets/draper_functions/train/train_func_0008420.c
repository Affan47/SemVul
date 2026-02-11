export_dialog_choose_file(GwyGraph *graph,
                          ExportParameters *params)
{
    GtkWidget *dialog;
    gchar *filename;
    GString *str;
    FILE *fw;

    dialog = gtk_file_chooser_dialog_new("Export to Text File", NULL,
                                         GTK_FILE_CHOOSER_ACTION_SAVE,
                                         GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                         GTK_STOCK_SAVE, GTK_RESPONSE_OK,
                                         NULL);
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_OK);
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),
                                        gwy_app_get_current_directory());

    switch (gtk_dialog_run(GTK_DIALOG(dialog))) {
        case GTK_RESPONSE_CANCEL:
        case GTK_RESPONSE_DELETE_EVENT:
        gtk_widget_destroy(dialog);
        case GTK_RESPONSE_NONE:
        return;
        break;

        case GTK_RESPONSE_OK:

        break;

        default:
        g_warning("Unhandled dialog response");
        return;
        break;
    }

    if (gwy_app_file_confirm_overwrite(dialog)) {
        GwyGraphModelExportStyle style;

        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        style = params->style | (params->posix
                                 ? GWY_GRAPH_MODEL_EXPORT_ASCII_POSIX
                                 : 0);
        str = gwy_graph_model_export_ascii(graph->graph_model,
                                           params->units,
                                           params->labels,
                                           params->metadata,
                                           style,
                                           NULL);


        fw = g_fopen(filename, "w");
        fwrite(str->str, str->len, 1, fw);
        fclose(fw);
        g_string_free(str, TRUE);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}
