ws_realloc(void *ptr, size_t size)
{
    if (size == 0) {
        if (ptr)
            free(ptr);

        return NULL;
    }

    if (ptr == NULL)
        return malloc(size);

    return realloc(ptr, size);
}
