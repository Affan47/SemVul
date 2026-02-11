scan_minimum(struct pma *p, int start, int size)
{
    int i;

    for (i=start; i < start + size; i++)
    {
        if (!empty(p->region, i))
            return p->region[i].key;
    }
    return 0;
}
