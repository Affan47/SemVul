mca_rcache_vma_tree_init(mca_rcache_vma_module_t* rcache)
{
    OBJ_CONSTRUCT(&rcache->rb_tree, ompi_rb_tree_t);
    OBJ_CONSTRUCT(&rcache->vma_list, opal_list_t);
    OBJ_CONSTRUCT(&rcache->vma_delete_list, opal_list_t);
    rcache->reg_cur_cache_size = 0;
    return ompi_rb_tree_init(&rcache->rb_tree,
                             mca_rcache_vma_tree_node_compare);
}
