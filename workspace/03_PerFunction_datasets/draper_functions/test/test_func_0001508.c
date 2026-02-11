ws_f_malloc(WsFastMalloc *pool, size_t size)
{
    unsigned char *result;


    if (size % sizeof(long) != 0) {
        size += sizeof(long) - (size % sizeof(long));
    }

    if (pool->size < size) {
        size_t alloc_size;
        WsFastMallocBlock *b;


        alloc_size = pool->block_size;
        if (alloc_size < size)
            alloc_size = size;


        b = ws_malloc(alloc_size + sizeof(WsFastMallocBlock));

        if (b == NULL)

            return NULL;


        b->next = pool->blocks;
        pool->blocks = b;

        pool->ptr = ((unsigned char *) b) + sizeof(WsFastMallocBlock);
        pool->size = alloc_size;
    }


    result = pool->ptr;

    pool->ptr += size;
    pool->size -= size;

    pool->user_bytes_allocated += size;

    return result;
}
