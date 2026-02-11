netsnmp_binary_array_get_subset(netsnmp_container *c, void *key, int *len)
{
    binary_array_table *t = (binary_array_table*)c->container_data;
    void          **subset;
    int             start, end;
    size_t          i;


    if (!c || !key)
        return NULL;

    t = (binary_array_table*)c->container_data;
    netsnmp_assert(c->ncompare);
    if (!t->count | !c->ncompare)
        return NULL;


    if (t->dirty)
        Sort_Array(c);


    start = end = binary_search_for_start((netsnmp_index *)key, c);
    if (start == -1)
        return NULL;

    for (i = start + 1; i < t->count; ++i) {
        if (0 != c->ncompare(t->data[i], key))
            break;
        ++end;
    }

    *len = end - start + 1;
    subset = (void **)malloc((*len) * sizeof(void*));
    if (subset)
        memcpy(subset, &t->data[start], sizeof(void*) * (*len));

    return subset;
}
