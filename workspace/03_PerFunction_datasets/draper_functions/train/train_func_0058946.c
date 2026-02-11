A_CFlameMissile(mobj_t * actor)
{
    int i;
    int an;
    fixed_t dist;
    mobj_t *mo;

    A_UnHideThing(actor);
    S_StartSound(actor, SFX_CLERIC_FLAME_EXPLODE);
    if (BlockingMobj && BlockingMobj->flags & MF_SHOOTABLE)
    {
        dist = BlockingMobj->radius + 18 * FRACUNIT;
        for (i = 0; i < 4; i++)
        {
            an = (i * ANG45) >> ANGLETOFINESHIFT;
            mo = P_SpawnMobj(BlockingMobj->x + FixedMul(dist, finecosine[an]),
                             BlockingMobj->y + FixedMul(dist, finesine[an]),
                             BlockingMobj->z + 5 * FRACUNIT, MT_CIRCLEFLAME);
            if (mo)
            {
                mo->angle = an << ANGLETOFINESHIFT;
                mo->target = actor->target;
                mo->momx = mo->special1.i =
                    FixedMul(FLAMESPEED, finecosine[an]);
                mo->momy = mo->special2.i = FixedMul(FLAMESPEED, finesine[an]);
                mo->tics -= P_Random() & 3;
            }
            mo = P_SpawnMobj(BlockingMobj->x - FixedMul(dist, finecosine[an]),
                             BlockingMobj->y - FixedMul(dist, finesine[an]),
                             BlockingMobj->z + 5 * FRACUNIT, MT_CIRCLEFLAME);
            if (mo)
            {
                mo->angle = ANG180 + (an << ANGLETOFINESHIFT);
                mo->target = actor->target;
                mo->momx = mo->special1.i = FixedMul(-FLAMESPEED,
                                                     finecosine[an]);
                mo->momy = mo->special2.i = FixedMul(-FLAMESPEED, finesine[an]);
                mo->tics -= P_Random() & 3;
            }
        }
        P_SetMobjState(actor, S_FLAMEPUFF2_1);
    }
}
