shrink_worm(int wnum)
{
    struct wseg *seg;

    if (wtails[wnum] == wheads[wnum])
    {
        return;
    }
    seg = wtails[wnum];
    wtails[wnum] = seg->nseg;
    seg->nseg = NULL;
    toss_wsegs(seg, true);
}
