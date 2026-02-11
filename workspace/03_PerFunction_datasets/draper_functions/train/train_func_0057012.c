mem_alloc_n(void *ptrptr, size_t size, size_t count)
{
    if (size == 0 || count == 0) {
        *(void **)ptrptr = NULL;
        return 0;
    }

    *(void**)ptrptr = calloc(count, size);
    if (*(void**)ptrptr == NULL)
        return -1;
    return 0;
}
