node_hash_from_list(GListPtr list)
{
    GListPtr gIter = list;
    GHashTable *result = g_hash_table_new_full(crm_str_hash, g_str_equal, NULL, g_hash_destroy_str);

    for (; gIter != NULL; gIter = gIter->next) {
        node_t *node = (node_t *) gIter->data;
        node_t *n = node_copy(node);

        g_hash_table_insert(result, (gpointer) n->details->id, n);
    }

    return result;
}
