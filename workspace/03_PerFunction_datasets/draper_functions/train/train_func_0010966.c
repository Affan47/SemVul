ufraw_overwrite_dialog(char *filename, GtkWidget *widget)
{
    char message[max_path];
    int response;
    GtkWidget *dialog = gtk_dialog_new_with_buttons(_("File exists"),
                        GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                        GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_NO_SEPARATOR,
                        GTK_STOCK_NO, GTK_RESPONSE_NO,
                        GTK_STOCK_YES, GTK_RESPONSE_YES, NULL);
    char *utf8 = g_filename_to_utf8(filename, -1, NULL, NULL, NULL);
    if (utf8 == NULL) utf8 = g_strdup("Unknown file name");
    snprintf(message, max_path,
             _("File '%s' already exists.\nOverwrite?"), utf8);
    g_free(utf8);
    GtkWidget *label = gtk_label_new(message);
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), label);
    gtk_widget_show_all(dialog);
    response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return (response == GTK_RESPONSE_YES);
}
