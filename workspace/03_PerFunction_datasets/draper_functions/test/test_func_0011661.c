mca_rcache_vma_can_insert(
        mca_rcache_vma_module_t *vma_rcache, size_t nbytes, size_t limit)
{
    if(0 == limit)
        return 1;

    if(vma_rcache->reg_cur_cache_size + nbytes <= limit)
        return 1;

    return 0;
}
