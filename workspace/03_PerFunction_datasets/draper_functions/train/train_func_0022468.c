density(struct pma *p, int start, int height, int *occupation)
{
    int occupied = 0;
    int i;


    int window_size = p->segsize * (1 << height);
    int window_start = start - start % window_size;
    int window_end = window_start + window_size;

    for (i = start; i >= window_start; i--)
        if (!empty(p->region, i))
            occupied++;

    for (i = start + 1; i < window_end; i++)
        if (!empty(p->region, i))
            occupied++;

    *occupation = occupied;

    return (double)occupied / window_size;
}
