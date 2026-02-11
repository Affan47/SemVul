P_SpawnMobj(fixed_t x, fixed_t y, fixed_t z, mobjtype_t type)
{
    mobj_t *mobj;
    state_t *st;
    mobjinfo_t *info;
    fixed_t space;

    mobj = Z_Malloc(sizeof(*mobj), PU_LEVEL, NULL);
    memset(mobj, 0, sizeof(*mobj));
    info = &mobjinfo[type];
    mobj->type = type;
    mobj->info = info;
    mobj->x = x;
    mobj->y = y;
    mobj->radius = info->radius;
    mobj->height = info->height;
    mobj->flags = info->flags;
    mobj->flags2 = info->flags2;
    mobj->damage = info->damage;
    mobj->health = info->spawnhealth;
    if (gameskill != sk_nightmare)
    {
        mobj->reactiontime = info->reactiontime;
    }
    mobj->lastlook = P_Random() % MAXPLAYERS;


    st = &states[info->spawnstate];
    mobj->state = st;
    mobj->tics = st->tics;
    mobj->sprite = st->sprite;
    mobj->frame = st->frame;


    P_SetThingPosition(mobj);
    mobj->floorz = mobj->subsector->sector->floorheight;
    mobj->ceilingz = mobj->subsector->sector->ceilingheight;
    if (z == ONFLOORZ)
    {
        mobj->z = mobj->floorz;
    }
    else if (z == ONCEILINGZ)
    {
        mobj->z = mobj->ceilingz - mobj->info->height;
    }
    else if (z == FLOATRANDZ)
    {
        space = ((mobj->ceilingz) - (mobj->info->height)) - mobj->floorz;
        if (space > 48 * FRACUNIT)
        {
            space -= 40 * FRACUNIT;
            mobj->z =
                ((space * P_Random()) >> 8) + mobj->floorz + 40 * FRACUNIT;
        }
        else
        {
            mobj->z = mobj->floorz;
        }
    }
    else
    {
        mobj->z = z;
    }
    if (mobj->flags2 & MF2_FOOTCLIP
        && P_GetThingFloorType(mobj) != FLOOR_SOLID
        && mobj->floorz == mobj->subsector->sector->floorheight)
    {
        mobj->flags2 |= MF2_FEETARECLIPPED;
    }
    else
    {
        mobj->flags2 &= ~MF2_FEETARECLIPPED;
    }

    mobj->thinker.function = P_MobjThinker;
    P_AddThinker(&mobj->thinker);
    return (mobj);
}
