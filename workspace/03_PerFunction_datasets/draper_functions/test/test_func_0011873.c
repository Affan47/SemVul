fs_hash_table_insert_node(fs_hash_table *hash_table,
        unsigned int node_index, unsigned int key_hash, void * key,
        void * value, int keep_new_key, int reusing_key) {
    unsigned int old_hash;
    void * old_key;
    void * old_value;

    if (FS_UNLIKELY(hash_table->keys == hash_table->values && key != value))
        hash_table->values = fs_memdup(hash_table->keys,
                sizeof(void *) * hash_table->size);

    old_hash = hash_table->hashes[node_index];
    old_key = hash_table->keys[node_index];
    old_value = hash_table->values[node_index];

    if (HASH_IS_REAL (old_hash)) {
        if (keep_new_key)
            hash_table->keys[node_index] = key;
        hash_table->values[node_index] = value;
    }
    else {
        hash_table->keys[node_index] = key;
        hash_table->values[node_index] = value;
        hash_table->hashes[node_index] = key_hash;

        hash_table->nnodes++;

        if (HASH_IS_UNUSED (old_hash)) {

            hash_table->noccupied++;
            fs_hash_table_maybe_resize(hash_table);
        }

#ifndef G_DISABLE_ASSERT
        hash_table->version++;
#endif
    }

    if (HASH_IS_REAL (old_hash)) {
        if (hash_table->key_destroy_func && !reusing_key)
            hash_table->key_destroy_func(keep_new_key ? old_key : key);
        if (hash_table->value_destroy_func)
            hash_table->value_destroy_func(old_value);
    }
}
