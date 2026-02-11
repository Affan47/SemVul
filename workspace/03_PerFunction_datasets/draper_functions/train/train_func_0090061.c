grow(ms a)
{
    void **nitems;
    size_t ncap = (a->cap << 1) ? : 1;

    nitems = malloc(ncap * sizeof(void *));
    if (!nitems) return;

    memcpy(nitems, a->items, a->used * sizeof(void *));
    free(a->items);
    a->items = nitems;
    a->cap = ncap;
}
