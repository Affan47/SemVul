wormhitu(worm)
    register struct monst *worm;
{
    register int wnum = worm->wormno;
    register struct wseg *seg;


    for (seg = wtails[wnum]; seg; seg = seg->nseg)
	if (distu(seg->wx, seg->wy) < 3)
	    (void) mattacku(worm);
}
