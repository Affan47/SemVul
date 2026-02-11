mca_mpool_base_tree_insert(mca_mpool_base_tree_item_t* item) {
    int rc;

    OPAL_THREAD_LOCK(&tree_lock);
    rc = ompi_rb_tree_insert(&mca_mpool_base_tree, item->key, item);
    OPAL_THREAD_UNLOCK(&tree_lock);

    return rc;
}
