find_umem(void *mem)
{
    UGLYMEM *nxtum = first;
    UGLYMEM *found = NULL;

    while (nxtum && (!found))
    {
	if (nxtum->ptr == mem)
	{
	    found = nxtum;
	}
	nxtum = nxtum->next;
    }

#if DEBUG_UGLY_MEMORY==2
    if (!found)
    {
	fprintf(stderr, "*memory* FIND_UMEM: couln't find %p\n", mem);
    }
#endif

    return (found);
}
