prefs_apply_list(gchar *key, GList *list) {
    GList *node;
    guint i;

    i = 0;

    if (prefs_table) {

        wipe_list(key);

        node = list;


        while (node) {
            g_hash_table_insert(prefs_table, create_full_key(key, i), g_strdup(node->data));

            node = g_list_next(node);
            i++;
        }


        g_hash_table_insert(prefs_table, create_full_key(key, i), g_strdup(LIST_END_MARKER));
    }
}
