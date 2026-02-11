visible_region_at(xchar x, xchar y)
{
    register int i;

    for (i = 0; i < n_regions; i++)
            if (inside_region(regions[i], x, y) && regions[i]->visible &&
                regions[i]->ttl != 0)
                    return regions[i];
    return (NhRegion *) 0;
}
