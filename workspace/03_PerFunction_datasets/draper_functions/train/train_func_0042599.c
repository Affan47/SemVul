iter_remove_or_steal(RealIter *ri, int notify) {
    g_return_if_fail(ri != NULL);
#ifndef G_DISABLE_ASSERT
    g_return_if_fail(ri->version == ri->hash_table->version);
#endif
    g_return_if_fail(ri->position >= 0);
    g_return_if_fail(ri->position < ri->hash_table->size);

    fs_hash_table_remove_node(ri->hash_table, ri->position, notify);

#ifndef G_DISABLE_ASSERT
    ri->version++;
    ri->hash_table->version++;
#endif
}
