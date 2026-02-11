prefs_free_list(GList *list) {
    GList *node;

    node = list;


    while (node) {
        if (node->data)
            g_free(node->data);

        node = g_list_next(node);
    }

    g_list_free(list);
}
