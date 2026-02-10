btree_printhead(btree_head* head)
{
    UInt32 attr;
    printf("  depth       : %#X\n",  head->depth);
    printf("  root        : %#lX\n", head->root);
    printf("  leaf_count  : %#lX\n", head->leaf_count);
    printf("  leaf_head   : %#lX\n", head->leaf_head);
    printf("  leaf_tail   : %#lX\n", head->leaf_tail);
    printf("  node_size   : %#X\n",  head->node_size);
    printf("  max_key_len : %#X\n",  head->max_key_len);
    printf("  node_count  : %#lX\n", head->node_count);
    printf("  free_nodes  : %#lX\n", head->free_nodes);
    printf("  reserved1   : %#X\n",  head->reserved1);
    printf("  clump_size  : %#lX\n", head->clump_size);
    printf("  btree_type  : %#X\n",  head->btree_type);
    attr = head->attributes;
    printf("  reserved2   : %#X\n",  head->reserved2);
    if (attr & HFSPLUS_BAD_CLOSE)
        printf(" HFSPLUS_BAD_CLOSE *** ");
    else
        printf(" !HFSPLUS_BAD_CLOSE");
    if (attr & HFSPLUS_TREE_BIGKEYS)
        printf(" HFSPLUS_TREE_BIGKEYS ");
    else
        printf("  !HFSPLUS_TREE_BIGKEYS");
    if (attr & HFSPLUS_TREE_VAR_NDXKEY_SIZE)
        printf(" HFSPLUS_TREE_VAR_NDXKEY_SIZE");
    else
        printf(" !HFSPLUS_TREE_VAR_NDXKEY_SIZE");
    if (attr & HFSPLUS_TREE_UNUSED)
        printf(" HFSPLUS_TREE_UNUSED ***\n");
    printf("\n");
}
