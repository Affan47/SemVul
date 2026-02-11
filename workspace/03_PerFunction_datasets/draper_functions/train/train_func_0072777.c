register_icon_path (const gchar* basedir, const gchar* dirname) {
    if (using_local()) {
        gchar *path = g_build_filename(basedir, dirname, "icons", NULL);
        gtk_icon_theme_append_search_path (gtk_icon_theme_get_default (), path);
        g_free(path);
    }
}
