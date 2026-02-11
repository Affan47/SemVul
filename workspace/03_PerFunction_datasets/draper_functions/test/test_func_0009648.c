spifmem_realloc(const spif_charptr_t var, const spif_charptr_t filename, unsigned long line, void *ptr, size_t size)
{
    void *temp;

#if MALLOC_CALL_DEBUG
    ++realloc_count;
    if (!(realloc_count % REALLOC_MOD)) {
        D_MEM(("Calls to realloc(): %d\n", realloc_count));
    }
#endif

    D_MEM(("Variable %s (%10p -> %lu) at %s:%lu\n", var, ptr, (unsigned long) size, NONULL(filename), line));
    if (ptr == NULL) {
        temp = (void *) spifmem_malloc(filename, line, size);
    } else if (size == 0) {
        spifmem_free(var, filename, line, ptr);
        temp = NULL;
    } else {
        temp = (void *) realloc(ptr, size);
        ASSERT_RVAL(!SPIF_PTR_ISNULL(temp), SPIF_NULL_TYPE(ptr));
        if (DEBUG_LEVEL >= DEBUG_MEM) {
            memrec_chg_var(&malloc_rec, var, SPIF_CAST(charptr) NONULL(filename), line, ptr, temp, size);
        }
    }
    return (temp);
}
