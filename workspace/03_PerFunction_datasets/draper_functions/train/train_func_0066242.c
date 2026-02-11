opal_calloc(size_t nmembers, size_t size, const char *file, int line)
{
    void *addr;
#if OPAL_ENABLE_DEBUG
    if (opal_malloc_debug_level > 1) {
        if (size <= 0) {
            opal_output(opal_malloc_output,
                        "Request for %ld zeroed elements of size %ld (%s, %d)",
                        (long) nmembers, (long) size, file, line);
        }
    }
#endif
    addr = calloc(nmembers, size);
#if OPAL_ENABLE_DEBUG
    if (opal_malloc_debug_level > 0) {
        if (NULL == addr) {
            opal_output(opal_malloc_output,
                        "Request for %ld zeroed elements of size %ld failed (%s, %d)",
                        (long) nmembers, (long) size, file, line);
        }
    }
#endif
    return addr;
}
