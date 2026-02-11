hostlist_iterator_new(void)
{
    hostlist_iterator_t i = (hostlist_iterator_t) malloc(sizeof(*i));
    if (!i)
        return NULL;
    i->hl = NULL;
    i->hr = NULL;
    i->idx = 0;
    i->depth = -1;
    i->next = i;
    assert(i->magic = HOSTLIST_MAGIC);
    return i;
}
