hash_free_nodes(hash_t *hash)
{
    hscan_t hs;
    hnode_t *node;
    hash_scan_begin(&hs, hash);
    while ((node = hash_scan_next(&hs))) {
        hash_scan_delete(hash, node);
        hash->freenode(node, hash->context);
    }
    hash->nodecount = 0;
    clear_table(hash);
}
