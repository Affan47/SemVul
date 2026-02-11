mca_memheap_ptmalloc_free(void* ptr)
{
    OPAL_THREAD_LOCK(&memheap_ptmalloc.lock);
    dlfree(ptr);
    OPAL_THREAD_UNLOCK(&memheap_ptmalloc.lock);
    return OSHMEM_SUCCESS;
}
