mrealloc(void *old_ptr, size_t old_size, size_t new_size)
{
    void *new_ptr = malloc(new_size);

    if (new_ptr == NULL)
        return NULL;


    if (old_ptr)
        memcpy(new_ptr, old_ptr, min(old_size, new_size));
    return new_ptr;
}
