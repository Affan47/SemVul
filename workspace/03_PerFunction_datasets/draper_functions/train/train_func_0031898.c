reAlloc(size_t size)
{
    if (size == 0)
    {
        free();
        return;
    }
    void* p = ::realloc(mMemory, size);
    if (p == NULL)
    {
        dbgerr("failed to allocate %lu bytes\n", size);
        return;
    }

    mMemory = p;
    mSize = size;
}
