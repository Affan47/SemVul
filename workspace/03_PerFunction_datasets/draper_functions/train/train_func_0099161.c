fluid_hashtable_insert_internal (fluid_hashtable_t *hashtable, void *key,
                                 void *value, int keep_new_key)
{
    fluid_hashnode_t **node_ptr, *node;
    unsigned int key_hash;

    fluid_return_if_fail (hashtable != NULL);
    fluid_return_if_fail (hashtable->ref_count > 0);

    node_ptr = fluid_hashtable_lookup_node (hashtable, key, &key_hash);

    if ((node = *node_ptr)) {
        if (keep_new_key) {
            if (hashtable->key_destroy_func)
                hashtable->key_destroy_func (node->key);
            node->key = key;
        } else {
            if (hashtable->key_destroy_func)
                hashtable->key_destroy_func (key);
        }

        if (hashtable->value_destroy_func)
            hashtable->value_destroy_func (node->value);

        node->value = value;
    } else {
        node = FLUID_NEW (fluid_hashnode_t);

        if (!node) {
            FLUID_LOG (FLUID_ERR, "Out of memory");
            return;
        }

        node->key = key;
        node->value = value;
        node->key_hash = key_hash;
        node->next = NULL;

        *node_ptr = node;
        hashtable->nnodes++;
        fluid_hashtable_maybe_resize (hashtable);
    }
}
