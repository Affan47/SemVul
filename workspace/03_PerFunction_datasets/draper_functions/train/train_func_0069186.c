new_hashtable(int desired, long maxmb)
{
    struct hashtable *t = calloc(sizeof *t, 1);

    if (!t) return NULL;

    if (desired < 1) desired = 65537;

    t->n = desired;
    t->e = calloc(sizeof *t->e, t->n);
    t->num = calloc(sizeof *t->num, t->n);
    if (maxmb > 0) {
        t->maxmem = maxmb * 1024 * 1024;
    }
    t->startmem = get_mem_usage(getpid());

    if (!t->e || !t->num)
        goto fail;

    return t;
fail:
    free(t->e);
    free(t->num);
    free(t);
    return NULL;
}
