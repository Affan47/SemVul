wormhitu(struct monst *worm)
{
    int wnum = worm->wormno;
    struct wseg *seg;


    for (seg = wtails[wnum]; seg; seg = seg->nseg)
    {
        if (distu(seg->wx, seg->wy) < 3)
        {
            mattacku(worm);
        }
    }
}
