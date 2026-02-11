all_5_bangles(EDGE **bang, int *nbang)


{
    int i,nb;
    EDGE *e,*elast;

    nb = 0;
    for (i = 0; i < nv; ++i)
    {
	e = elast = firstedge[i];
	do
	{
	    if (e == e->min && is_in_5_bangle(e)) bang[nb++] = e;
	    e = e->next;
	} while (e != elast);
    }

    *nbang = nb;
}
