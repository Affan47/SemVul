prefs_get_list(const gchar *key) {
    guint end_marker_hash;
    guint item_hash;
    gchar *item_string = NULL;
    guint i = 0;
    GList *list = NULL;


    end_marker_hash = g_str_hash(LIST_END_MARKER);


    do {
        item_string = prefs_get_string_index(key, i);

        if (item_string) {
            item_hash = g_str_hash(item_string);
            if (item_hash != end_marker_hash) {
                list = g_list_append(list, item_string);
            }
        }
        i++;
    }
    while (item_string != NULL && item_hash != end_marker_hash);

    return list;
}
