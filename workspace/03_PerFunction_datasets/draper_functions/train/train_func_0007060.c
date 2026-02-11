emalloc(size_t size)
{
    void *p = malloc(size);

    if (p == NULL) {
        RAISE(MEM_ERROR, "failed to allocate %d bytes", (int)size);
    }

    return p;
}
