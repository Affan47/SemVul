finish_editable_storage(gchar *key, GtkEditable *editable) {
    gchar *str;

    g_return_val_if_fail (repository_view && key && editable, FALSE);

    str = gtk_editable_get_chars(editable, 0, -1);
    return finish_string_storage(key, str);
}
