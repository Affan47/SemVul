P_SpawnMapThing (mapthing_t* mthing)
{
    int         i;
    int         bit;
    mobj_t*     mobj;
    fixed_t     x;
    fixed_t     y;
    fixed_t     z;


    if (mthing->type == 11)
    {
        if (deathmatch_p < &deathmatchstarts[10])
        {
            memcpy (deathmatch_p, mthing, sizeof(*mthing));
            deathmatch_p++;
        }
        return;
    }

    if (mthing->type <= 0)
    {


        return;
    }


    if (mthing->type <= 8)
    {

        playerstarts[mthing->type-1] = *mthing;
        if (!deathmatch)
            P_SpawnPlayer (mthing);

        return;
    }


    if (!netgame && (mthing->options & 16) )
        return;

    if (gameskill == sk_baby)
        bit = 1;
    else if (gameskill == sk_nightmare)
        bit = 4;
    else
        bit = 1<<(gameskill-1);

    if (!(mthing->options & bit) )
        return;


    for (i=0 ; i< NUMMOBJTYPES ; i++)
        if (mthing->type == mobjinfo[i].doomednum)
            break;

    if (i==NUMMOBJTYPES)
        I_Error ("P_SpawnMapThing: Unknown type %i at (%i, %i)",
                 mthing->type,
                 mthing->x, mthing->y);


    if (deathmatch && mobjinfo[i].flags & MF_NOTDMATCH)
        return;


    if (nomonsters && (mobjinfo[i].flags & MF_COUNTKILL))
        return;


    x = mthing->x << FRACBITS;
    y = mthing->y << FRACBITS;

    if (mobjinfo[i].flags & MF_SPAWNCEILING)
        z = ONCEILINGZ;
    else
        z = ONFLOORZ;

    mobj = P_SpawnMobj (x,y,z, i);
    mobj->spawnpoint = *mthing;

    if (mobj->tics > 0)
        mobj->tics = 1 + (P_Random () % mobj->tics);
    if (mobj->flags & MF_COUNTKILL)
        totalkills++;


    mobj->angle = ANG45 * (mthing->angle/45);
    if (mthing->options & MTF_AMBUSH)
        mobj->flags |= MF_AMBUSH;
    if (mthing->options & MTF_STAND)
        mobj->flags |= MF_STAND;
    if (mthing->options & MTF_FRIEND)
        mobj->flags |= MF_ALLY;
    if (mthing->options & MTF_TRANSLUCENT)
        mobj->flags |= MF_SHADOW;
    if (mthing->options & MTF_MVIS)
        mobj->flags |= MF_MVIS;
}
