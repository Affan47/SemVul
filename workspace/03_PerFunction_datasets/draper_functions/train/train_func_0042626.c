pathnode_dump(int fd, PathNodeTree pnt, int shrink)
{
    double rl, rr;
    if (pnt->num_left > pnt->num_right) {
	rl = (double)pnt->num_left / pnt->num_right;
	rr = 1.0;
    } else {
	rl = 1.0;
	rr = (double)pnt->num_right / pnt->num_left;
    }
    DPRINT(("pathnode: %d entries, new %d alloc, left %d entries\n"
	    "   left=%d times, right=%d times  (%f:%f)\n",
	    pnt->num_pn, pnt->pn_alloc, pnt->pn_avail,
	    pnt->num_left, pnt->num_right, rl, rr));
    if (shrink) {
	mempool_shrink(pnt->p_st, pnt->pn_avail);
	pnt->pn_avail = 0;
    }
    DPRINT(("pathnode: dump "));
    return mempool_dump(pnt->p_st, fd, pathnode_serialize, pnt);
}
