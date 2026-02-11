gtkpod_register_filetype(FileType *filetype) {
    g_return_if_fail(FILE_IS_TYPE(filetype));
    g_return_if_fail(GTKPOD_IS_APP(gtkpod_app));
    GtkPodAppInterface *gp_iface = GTKPOD_APP_GET_INTERFACE (gtkpod_app);
    GList *s;

    GList *suffixes = filetype_get_suffixes(filetype);
    if (!suffixes)
        return;

    s = suffixes;
    while(s) {
        gchar *uc = g_ascii_strup(s->data, -1);
        g_hash_table_insert(gp_iface->filetypes, s->data, filetype);
        g_hash_table_insert(gp_iface->filetypes, uc, filetype);
        s = g_list_next(s);
    }
}
