tracemalloc_free(void *ctx, void *ptr)
{
    PyMemAllocator *alloc = (PyMemAllocator *)ctx;

    if (ptr == NULL)
        return;


    alloc->free(alloc->ctx, ptr);

    TABLES_LOCK();
    tracemalloc_remove_trace(ptr);
    TABLES_UNLOCK();
}
