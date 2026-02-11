osinfo_list_add_intersection(OsinfoList *list, OsinfoList *sourceOne, OsinfoList *sourceTwo)
{
    int i, len;
    g_return_if_fail(list->priv->elementType == sourceOne->priv->elementType);
    g_return_if_fail(list->priv->elementType == sourceTwo->priv->elementType);


    GHashTable *otherSet = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    GHashTable *newSet = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);


    len = osinfo_list_get_length(sourceTwo);
    for (i = 0; i < len; i++) {
        OsinfoEntity *entity = osinfo_list_get_nth(sourceTwo, i);
        g_hash_table_insert(otherSet, g_strdup(osinfo_entity_get_id(entity)), entity);
    }


    len = osinfo_list_get_length(sourceOne);
    for (i = 0; i < len; i++) {
        OsinfoEntity *entity = osinfo_list_get_nth(sourceOne, i);

        if (g_hash_table_lookup(otherSet, osinfo_entity_get_id(entity)) &&
            !g_hash_table_lookup(newSet, osinfo_entity_get_id(entity))) {
            g_hash_table_insert(newSet, g_strdup(osinfo_entity_get_id(entity)), entity);
            osinfo_list_add(list, entity);
        }
    }

    g_hash_table_destroy(otherSet);
    g_hash_table_destroy(newSet);
}
