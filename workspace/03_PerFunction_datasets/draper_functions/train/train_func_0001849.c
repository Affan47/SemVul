malloc_bytes(size_t size)
{
    int i,j;
    u_int u;
    struct  pginfo *bp;
    int k;
    u_int *lp;


    if (size < malloc_minsize)
	size = malloc_minsize;


    j = 1;
    i = size-1;
    while (i >>= 1)
	j++;


    if (!page_dir[j] && !malloc_make_chunks(j))
	return 0;

    bp = page_dir[j];


    for (lp = bp->bits; !*lp; lp++)
	;


    u = 1;
    k = 0;
    while (!(*lp & u)) {
	u += u;
	k++;
    }
    *lp ^= u;


    if (!--bp->free) {
	page_dir[j] = bp->next;
	bp->next = 0;
    }


    k += (lp-bp->bits)*MALLOC_BITS;
    k <<= bp->shift;

    if (malloc_junk)
	memset((u_char*)bp->page + k, SOME_JUNK, bp->size);

    return (u_char *)bp->page + k;
}
