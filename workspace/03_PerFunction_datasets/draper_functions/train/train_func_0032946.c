spl_limitvalue_changed(GtkEditable *editable, GtkWidget *spl_window) {
    Playlist *spl;
    gchar *str;

    g_return_if_fail (spl_window);
    spl = g_object_get_data(G_OBJECT (spl_window), "spl_work");
    g_return_if_fail (spl);
    str = gtk_editable_get_chars(editable, 0, -1);
    spl->splpref.limitvalue = atol(str);
    g_free(str);
}
