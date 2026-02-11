fluid_hashtable_get_keys (fluid_hashtable_t *hashtable)
{
    fluid_hashnode_t *node;
    int i;
    fluid_list_t *retval;

    fluid_return_val_if_fail (hashtable != NULL, NULL);

    retval = NULL;
    for (i = 0; i < hashtable->size; i++)
        for (node = hashtable->nodes[i]; node; node = node->next)
            retval = fluid_list_prepend (retval, node->key);

    return retval;
}
