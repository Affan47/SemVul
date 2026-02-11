range_new(int begin, int end, int n_arrays)
{
    Range *r;

    r = (Range *)malloc(sizeof(Range));
    if (r == NULL)
        fatal("malloc failed\n");
    r->begin = begin;
    r->end = end;
    r->n_arrays = n_arrays;
    r->next = NULL;

    return r;
}
