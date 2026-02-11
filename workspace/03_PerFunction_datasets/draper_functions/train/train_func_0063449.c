P_HitFloor(mobj_t * thing)
{
    mobj_t *mo;

    if (thing->floorz != thing->subsector->sector->floorheight)
    {
        return (FLOOR_SOLID);
    }
    switch (P_GetThingFloorType(thing))
    {
        case FLOOR_WATER:
            P_SpawnMobj(thing->x, thing->y, ONFLOORZ, MT_SPLASHBASE);
            mo = P_SpawnMobj(thing->x, thing->y, ONFLOORZ, MT_SPLASH);
            mo->target = thing;
            mo->momx = (P_Random() - P_Random()) << 8;
            mo->momy = (P_Random() - P_Random()) << 8;
            mo->momz = 2 * FRACUNIT + (P_Random() << 8);
            S_StartSound(mo, sfx_gloop);
            return (FLOOR_WATER);
        case FLOOR_LAVA:
            P_SpawnMobj(thing->x, thing->y, ONFLOORZ, MT_LAVASPLASH);
            mo = P_SpawnMobj(thing->x, thing->y, ONFLOORZ, MT_LAVASMOKE);
            mo->momz = FRACUNIT + (P_Random() << 7);
            S_StartSound(mo, sfx_burn);
            return (FLOOR_LAVA);
        case FLOOR_SLUDGE:
            P_SpawnMobj(thing->x, thing->y, ONFLOORZ, MT_SLUDGESPLASH);
            mo = P_SpawnMobj(thing->x, thing->y, ONFLOORZ, MT_SLUDGECHUNK);
            mo->target = thing;
            mo->momx = (P_Random() - P_Random()) << 8;
            mo->momy = (P_Random() - P_Random()) << 8;
            mo->momz = FRACUNIT + (P_Random() << 8);
            return (FLOOR_SLUDGE);
    }
    return (FLOOR_SOLID);
}
