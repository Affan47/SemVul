qof_query_core_shutdown (void)
{
    if (!initialized) return;
    initialized = FALSE;

    g_hash_table_destroy (predTable);
    g_hash_table_destroy (cmpTable);
    g_hash_table_destroy (copyTable);
    g_hash_table_destroy (freeTable);
    g_hash_table_destroy (toStringTable);
    g_hash_table_destroy (predEqualTable);
}
