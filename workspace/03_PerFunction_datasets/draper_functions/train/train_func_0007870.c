get_header(GC_Heap *gh, void *ptr)
{
    Header *p, *pend, *pnext;

    pend = (Header *)(((size_t)gh->slot) + gh->size);
    for (p = gh->slot; p < pend; p = pnext) {
        pnext = NEXT_HEADER(p);
        if ((void *)(p+1) <= ptr && ptr < (void *)pnext) {
            return p;
        }
    }
    return NULL;
}
