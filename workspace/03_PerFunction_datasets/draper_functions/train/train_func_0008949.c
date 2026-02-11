mpool_destroy(mpool_handle_t pool)
{
    mpool_mem_t *ptr, *next;

    MPOOL_LOCK();

    for (ptr = pool; ptr; ptr = next) {
        next = ptr->next;
        FREE(ptr);
    }

    MPOOL_UNLOCK();

    return 0;
}
