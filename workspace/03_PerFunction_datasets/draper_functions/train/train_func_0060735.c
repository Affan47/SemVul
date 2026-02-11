mpool_create(void *base_ptr, int size)
{
    mpool_mem_t *head, *tail;
    int mod = (int)(((unsigned long)base_ptr) & (BCM_CACHE_LINE_BYTES - 1));

    MPOOL_LOCK();

    if (mod) {
        base_ptr = (char*)base_ptr + (BCM_CACHE_LINE_BYTES - mod);
        size -= (BCM_CACHE_LINE_BYTES - mod);
    }
    size &= ~(BCM_CACHE_LINE_BYTES - 1);


    head = (mpool_mem_t *)MALLOC(sizeof(mpool_mem_t));
    if (head == NULL) {
        return NULL;
    }
    tail = (mpool_mem_t *)MALLOC(sizeof(mpool_mem_t));
    if (tail == NULL) {
        FREE(head);
        return NULL;
    }

    head->size = tail->size = 0;
    head->address = base_ptr;
    tail->address = head->address + size;
    head->next = tail;
    tail->next = NULL;

    MPOOL_UNLOCK();

    return head;
}
