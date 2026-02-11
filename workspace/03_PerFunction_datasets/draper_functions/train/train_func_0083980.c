fs_hash_table_remove_all(fs_hash_table *hash_table) {
    g_return_if_fail(hash_table != NULL);

#ifndef G_DISABLE_ASSERT
    if (hash_table->nnodes != 0)
        hash_table->version++;
#endif

    fs_hash_table_remove_all_nodes(hash_table, TRUE);
    fs_hash_table_maybe_resize(hash_table);
}
