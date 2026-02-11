agedgeidcmpf(Dict_t * d, void *arg_e0, void *arg_e1, Dtdisc_t * disc)
{
    long v;
    Agedge_t *e0, *e1;

    NOTUSED(d);
    e0 = arg_e0;
    e1 = arg_e1;
    NOTUSED(disc);
    v = AGID(e0->node) - AGID(e1->node);
    if (v == 0) {
	if ((AGTYPE(e0) == 0) || (AGTYPE(e1) == 0))
	    v = 0;
	else
	    v = AGID(e0) - AGID(e1);
    }
    return ((v==0)?0:(v<0?-1:1));
}
