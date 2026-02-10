template_setup (GuTemplate* t) {
    const gchar *filename;
    char *filepath = NULL;
    GError *error = NULL;
    GtkTreeIter iter;

    gchar *dirpath = g_build_filename (g_get_user_config_dir (), "gummi",
                                      "templates" , NULL);

    GDir* dir = g_dir_open (dirpath, 0, &error);
    if (error) {

        slog (L_INFO, "unable to read template directory, creating new..\n");
        g_mkdir_with_parents (dirpath, DIR_PERMS);
        g_free (dirpath);
        return;
    }

    while ( (filename = g_dir_read_name (dir))) {
        filepath = g_build_filename (dirpath, filename, NULL);
        gtk_list_store_append (t->list_templates, &iter);
        gtk_list_store_set (t->list_templates, &iter, 0, filename, 1,
                filepath, -1);
        g_free (filepath);
    }
    g_free (dirpath);


    if (!tabmanager_has_tabs()) {
        gtk_widget_set_sensitive (t->template_add, FALSE);
    }

    gtk_widget_set_sensitive (t->template_open, FALSE);


}
