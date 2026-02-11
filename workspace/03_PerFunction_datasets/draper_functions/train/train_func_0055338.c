P_RadiusAttack(mobj_t * spot, mobj_t * source, int damage)
{
    int x, y, xl, xh, yl, yh;
    fixed_t dist;

    dist = (damage + MAXRADIUS) << FRACBITS;
    yh = (spot->y + dist - bmaporgy) >> MAPBLOCKSHIFT;
    yl = (spot->y - dist - bmaporgy) >> MAPBLOCKSHIFT;
    xh = (spot->x + dist - bmaporgx) >> MAPBLOCKSHIFT;
    xl = (spot->x - dist - bmaporgx) >> MAPBLOCKSHIFT;
    bombspot = spot;
    if (spot->type == MT_POD && spot->target)
    {
        bombsource = spot->target;
    }
    else
    {
        bombsource = source;
    }
    bombdamage = damage;
    for (y = yl; y <= yh; y++)
        for (x = xl; x <= xh; x++)
            P_BlockThingsIterator(x, y, PIT_RadiusAttack);
}
