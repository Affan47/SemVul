gcut_hash_table_equal (GHashTable *hash1, GHashTable *hash2,
                       GEqualFunc equal_func)
{
    EqualData data;

    if (hash1 == NULL && hash2 == NULL)
        return TRUE;

    if (hash1 == NULL || hash2 == NULL)
        return FALSE;

    if (g_hash_table_size(hash1) != g_hash_table_size(hash2))
        return FALSE;

    data.target = hash2;
    data.equal_func = equal_func;
    data.equal = TRUE;
    g_hash_table_foreach(hash1, equal_hash_table_pair, &data);

    return data.equal;
}
