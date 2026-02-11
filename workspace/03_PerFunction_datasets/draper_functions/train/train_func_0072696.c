mca_rcache_vma_tree_finalize(mca_rcache_vma_module_t* rcache)
{
    ompi_rb_tree_init(&rcache->rb_tree,
                      mca_rcache_vma_tree_node_compare);
    OBJ_DESTRUCT(&rcache->vma_delete_list);
    OBJ_DESTRUCT(&rcache->vma_list);
    OBJ_DESTRUCT(&rcache->rb_tree);
}
