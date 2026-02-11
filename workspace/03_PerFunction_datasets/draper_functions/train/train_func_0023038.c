P_UpdateChicken(mobj_t * actor, int tics)
{
    mobj_t *fog;
    fixed_t x;
    fixed_t y;
    fixed_t z;
    mobjtype_t moType;
    mobj_t *mo;
    mobj_t oldChicken;

    actor->special1.i -= tics;
    if (actor->special1.i > 0)
    {
        return (false);
    }
    moType = actor->special2.i;
    x = actor->x;
    y = actor->y;
    z = actor->z;
    oldChicken = *actor;
    P_SetMobjState(actor, S_FREETARGMOBJ);
    mo = P_SpawnMobj(x, y, z, moType);
    if (P_TestMobjLocation(mo) == false)
    {
        P_RemoveMobj(mo);
        mo = P_SpawnMobj(x, y, z, MT_CHICKEN);
        mo->angle = oldChicken.angle;
        mo->flags = oldChicken.flags;
        mo->health = oldChicken.health;
        mo->target = oldChicken.target;
        mo->special1.i = 5 * 35;
        mo->special2.i = moType;
        return (false);
    }
    mo->angle = oldChicken.angle;
    mo->target = oldChicken.target;
    fog = P_SpawnMobj(x, y, z + TELEFOGHEIGHT, MT_TFOG);
    S_StartSound(fog, sfx_telept);
    return (true);
}
