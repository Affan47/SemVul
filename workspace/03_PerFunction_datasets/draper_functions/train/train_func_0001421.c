allocation_grow(struct allocation **alloc, unsigned int *size) {
    void *ptr = realloc(*alloc, (*size * 2 + 1) * sizeof(**alloc));

    if (ptr) {
        *alloc = ptr;
        *size = *size * 2 + 1;
        return 1;
    } else {
        return 0;
    }
}
