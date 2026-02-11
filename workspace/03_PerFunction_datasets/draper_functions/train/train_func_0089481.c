hash_delete(hash_t *hash, hnode_t *node)
{
    hash_val_t chain;
    hnode_t *hptr;

    assert (hash_lookup(hash, node->key) == node);
    assert (hash_val_t_bit != 0);

    if (hash->dynamic && hash->nodecount <= hash->lowmark
            && hash->nodecount > INIT_SIZE)
        shrink_table(hash);

    chain = node->hkey & hash->mask;
    hptr = hash->table[chain];

    if (hptr == node) {
        hash->table[chain] = node->next;
    } else {
        while (hptr->next != node) {
            assert (hptr != 0);
            hptr = hptr->next;
        }
        assert (hptr->next == node);
        hptr->next = node->next;
    }

    hash->nodecount--;
    assert (hash_verify(hash));

    node->next = NULL;
    return node;
}
