arrow_gen_type(GVJ_t * job, pointf p, pointf u, double arrowsize, double penwidth, int flag)
{
    int f;
    arrowtype_t *arrowtype;

    f = flag & ((1 << BITS_PER_ARROW_TYPE) - 1);
    for (arrowtype = Arrowtypes; arrowtype->type; arrowtype++) {
	if (f == arrowtype->type) {
	    u.x *= arrowtype->lenfact * arrowsize;
	    u.y *= arrowtype->lenfact * arrowsize;
	    (arrowtype->gen) (job, p, u, arrowsize, penwidth, flag);
	    p.x = p.x + u.x;
	    p.y = p.y + u.y;
	    break;
	}
    }
    return p;
}
