update_nft_four(triangle nft[], int numnft, EDGE *ref,
                triangle newnft[], int *newnumnft)


{
    EDGE *refmin,*e,*elast;
    int i,k,w;

    refmin = ref->min;


    k = 0;
    for (i = 0; i < numnft; ++i)
        if (nft[i].e1 != refmin && nft[i].e2 != refmin && nft[i].e3 != refmin)
            newnft[k++] = nft[i];


    if (k >= 2)
    {
        w = ref->next->end;
        elast = ref->invers->next->invers;
        for (e = elast->next->next->next; e != elast; e = e->next)
            if (e->end == w) break;
        if (e != elast)
        {
            newnft[k].e1 = e->min;
            newnft[k].e2 = ref->prev->min;
            newnft[k].e3 = ref->next->min;
            ++k;
        }
    }
    *newnumnft = k;
}
