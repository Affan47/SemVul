EV_BuildStairs
( line_t*	line,
  stair_e	type )
{
    int                 secnum;
    int                 height;
    int                 i;
    int                 newsecnum;
    int                 texture;
    int                 ok;
    int                 rtn;

    sector_t*           sec;
    sector_t*           tsec;

    floormove_t*        floor;


    fixed_t             stairsize = 8*FRACUNIT;
    fixed_t             speed     = FLOORSPEED;
    int                 direction = 1;

    switch(type)
    {
    case build8:
        speed = FLOORSPEED/4;
        break;
    case turbo16:
        speed = FLOORSPEED*4;
        stairsize = 16*FRACUNIT;
        break;
    case buildDown16:
        stairsize = -16*FRACUNIT;
        direction = -1;
        break;
    }

    secnum = -1;
    rtn = 0;
    while ((secnum = P_FindSectorFromLineTag(line,secnum)) >= 0)
    {
        sec = &sectors[secnum];


        if (sec->specialdata)
            continue;


        rtn = 1;
        floor = Z_Malloc (sizeof(*floor), PU_LEVSPEC, 0);
        P_AddThinker (&floor->thinker);
        sec->specialdata = floor;
        floor->thinker.function.acp1 = (actionf_p1) T_MoveFloor;
        floor->direction = 1;
        floor->sector = sec;
        floor->speed = speed;
        height = sec->floorheight + stairsize;
        floor->floordestheight = height;

        texture = sec->floorpic;


        do
        {
            ok = 0;
            for (i = 0;i < sec->linecount;i++)
            {
                if ( !((sec->lines[i])->flags & ML_TWOSIDED) )
                    continue;

                tsec = (sec->lines[i])->frontsector;
                newsecnum = tsec-sectors;

                if (secnum != newsecnum)
                    continue;

                tsec = (sec->lines[i])->backsector;
                newsecnum = tsec - sectors;

                if (tsec->floorpic != texture)
                    continue;

                height += stairsize;

                if (tsec->specialdata)
                    continue;

                sec = tsec;
                secnum = newsecnum;
                floor = Z_Malloc (sizeof(*floor), PU_LEVSPEC, 0);

                P_AddThinker (&floor->thinker);

                sec->specialdata = floor;
                floor->thinker.function.acp1 = (actionf_p1) T_MoveFloor;
                floor->direction = direction;
                floor->sector = sec;
                floor->speed = speed;
                floor->floordestheight = height;
                ok = 1;
                break;
            }
        } while(ok);
    }
    return rtn;
}
