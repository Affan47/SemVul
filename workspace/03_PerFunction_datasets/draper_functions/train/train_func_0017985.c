min5_b_legal(EDGE *ref, int mirror, EDGE *good_or[], int *ngood_or,
   int *ngood_ref, EDGE *good_mir[], int *ngood_mir, int *ngood_mir_ref)


{
    EDGE *e,*elast;
    int nor,nmir,i;

    ref = ref->min;
    nor = nmir = 0;

    if (!mirror)
    {
	good_or[nor++] = ref;
	good_or[nor++] = ref->invers;
    }
    else
    {
	good_mir[nmir++] = ref;
	good_mir[nmir++] = ref->invers;
    }

    *ngood_ref = nor;
    *ngood_mir_ref = nmir;

    RESETMARKS;
    MARKLO(ref);

    for (i = 0; i < nv; ++i)
    if (degree[i] == 5)
    {
	e = elast = firstedge[i];
	do
	{
	    if (e == e->min && !ISMARKEDLO(e) && degree[e->prev->end] == 5
			&& degree[e->end] == 5 && degree[e->next->end] == 5)
	    {
		if (is_valid_min5_b(e,FALSE))
		{
        	    good_or[nor++] = e;
        	    good_or[nor++] = e->invers;
    		}
		if (is_valid_min5_b(e,TRUE))
		{
        	    good_mir[nmir++] = e;
        	    good_mir[nmir++] = e->invers;
		}
	    }
	    e = e->next;
	} while (e != elast);
    }

    if (nor > *ngood_ref || nmir > *ngood_mir_ref)
        prune_oriented_lists(good_or,&nor,ngood_ref,
                             good_mir,&nmir,ngood_mir_ref);

    *ngood_or = nor;
    *ngood_mir = nmir;
}
