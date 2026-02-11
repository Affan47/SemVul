insert_value(GHashTable *hash_table, char *key, char *value)
    {
    GSList *slist = NULL;
    gpointer orig_key = NULL;

    if (g_hash_table_lookup_extended(hash_table, key, &orig_key, (gpointer *)&slist))
        {
        g_hash_table_steal(hash_table, key);
        free(orig_key);
        }

    slist = g_slist_append(slist, (gpointer)value);
    g_hash_table_insert(hash_table, key, (gpointer)slist);
    }
