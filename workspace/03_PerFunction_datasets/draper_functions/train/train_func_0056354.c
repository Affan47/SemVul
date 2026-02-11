dst_filesel_ok(struct w *widgets)
{

    gchar *utf8 = NULL;

    G_CONST_RETURN gchar *path = gtk_file_selection_get_filename(GTK_FILE_SELECTION(widgets->dst_filesel));
    utf8 = g_locale_to_utf8(path, strlen(path), NULL, NULL, NULL);


    gtk_list_store_set(widgets->backup_store, &iter_filesel, 3, utf8, -1);

    gtk_list_store_set(widgets->backup_store, &iter_filesel, 6, TRUE, -1);

    if( utf8!=NULL )
      g_free(utf8);

    gtk_widget_destroy(widgets->dst_filesel);


    save_backup_settings(widgets);
}
