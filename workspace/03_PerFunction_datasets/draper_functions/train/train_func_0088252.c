xrealloc(void *p, size_t size) {

    if (size == 0) {
        free(p);
        return NULL;
    }

    if (!(p = realloc(p, size)))
        oom();

    return p;
}
