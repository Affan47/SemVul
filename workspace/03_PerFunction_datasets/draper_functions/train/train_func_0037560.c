insertEdge(Dt_t * map, void *t, void *h, edge_t * e)
{
    item dummy;

    dummy.p[0] = t;
    dummy.p[1] = h;
    dummy.t = agtail(e);
    dummy.h = aghead(e);
    dtinsert(map, &dummy);

    dummy.p[0] = h;
    dummy.p[1] = t;
    dummy.t = aghead(e);
    dummy.h = agtail(e);
    dtinsert(map, &dummy);
}
