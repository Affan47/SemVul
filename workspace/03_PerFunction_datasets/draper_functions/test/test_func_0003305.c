P_SightBlockLinesIterator(int x, int y)
{
    int offset;
    short *list;
    line_t *ld;
    int s1, s2;
    divline_t dl;

    polyblock_t *polyLink;
    seg_t **segList;
    int i;
    extern polyblock_t **PolyBlockMap;

    offset = y * bmapwidth + x;

    polyLink = PolyBlockMap[offset];
    while (polyLink)
    {
        if (polyLink->polyobj)
        {
            if (polyLink->polyobj->validcount != validcount)
            {
                segList = polyLink->polyobj->segs;
                for (i = 0; i < polyLink->polyobj->numsegs; i++, segList++)
                {
                    ld = (*segList)->linedef;
                    if (ld->validcount == validcount)
                    {
                        continue;
                    }
                    ld->validcount = validcount;
                    s1 = P_PointOnDivlineSide(ld->v1->x, ld->v1->y, &trace);
                    s2 = P_PointOnDivlineSide(ld->v2->x, ld->v2->y, &trace);
                    if (s1 == s2)
                        continue;
                    P_MakeDivline(ld, &dl);
                    s1 = P_PointOnDivlineSide(trace.x, trace.y, &dl);
                    s2 = P_PointOnDivlineSide(trace.x + trace.dx,
                                              trace.y + trace.dy, &dl);
                    if (s1 == s2)
                        continue;


                    if (!ld->backsector)
                        return false;


                    intercept_p->d.line = ld;
                    intercept_p++;
                }
                polyLink->polyobj->validcount = validcount;
            }
        }
        polyLink = polyLink->next;
    }

    offset = *(blockmap + offset);

    for (list = blockmaplump + offset; *list != -1; list++)
    {
        ld = &lines[*list];
        if (ld->validcount == validcount)
            continue;
        ld->validcount = validcount;

        s1 = P_PointOnDivlineSide(ld->v1->x, ld->v1->y, &trace);
        s2 = P_PointOnDivlineSide(ld->v2->x, ld->v2->y, &trace);
        if (s1 == s2)
            continue;
        P_MakeDivline(ld, &dl);
        s1 = P_PointOnDivlineSide(trace.x, trace.y, &dl);
        s2 = P_PointOnDivlineSide(trace.x + trace.dx, trace.y + trace.dy,
                                  &dl);
        if (s1 == s2)
            continue;


        if (!ld->backsector)
            return false;


        intercept_p->d.line = ld;
        intercept_p++;

    }

    return true;
}
