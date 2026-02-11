P_SetThingPosition(mobj_t * thing)
{
    subsector_t *ss;
    sector_t *sec;
    int blockx, blocky;
    mobj_t **link;


    ss = R_PointInSubsector(thing->x, thing->y);
    thing->subsector = ss;
    if (!(thing->flags & MF_NOSECTOR))
    {
        sec = ss->sector;

        thing->sprev = NULL;
        thing->snext = sec->thinglist;
        if (sec->thinglist)
            sec->thinglist->sprev = thing;
        sec->thinglist = thing;
    }


    if (!(thing->flags & MF_NOBLOCKMAP))
    {
        blockx = (thing->x - bmaporgx) >> MAPBLOCKSHIFT;
        blocky = (thing->y - bmaporgy) >> MAPBLOCKSHIFT;
        if (blockx >= 0 && blockx < bmapwidth && blocky >= 0
            && blocky < bmapheight)
        {
            link = &blocklinks[blocky * bmapwidth + blockx];
            thing->bprev = NULL;
            thing->bnext = *link;
            if (*link)
                (*link)->bprev = thing;
            *link = thing;
        }
        else
        {
            thing->bnext = thing->bprev = NULL;
        }
    }
}
