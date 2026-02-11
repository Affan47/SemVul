A_BurnSpread(mobj_t* actor)
{
    int t;
    mobj_t* mo;
    fixed_t x;
    fixed_t y;

    actor->momz -= (8*FRACUNIT);

    t = P_Random();
    actor->momx += ((t & 3) - (P_Random() & 3)) << FRACBITS;
    t = P_Random();
    actor->momy += ((t & 3) - (P_Random() & 3)) << FRACBITS;

    S_StartSound(actor, sfx_lgfire);

    if(actor->flags & MF_DROPPED)
        return;


    y = actor->y + (((P_Random() + 12) & 31) << FRACBITS);
    x = actor->x + (((P_Random() + 12) & 31) << FRACBITS);


    mo = P_SpawnMobj(x, y, actor->z + (4*FRACUNIT), MT_PFLAME);

    t = P_Random();
    mo->momx += ((t & 7) - (P_Random() & 7)) << FRACBITS;
    t = P_Random();
    mo->momy += ((t & 7) - (P_Random() & 7)) << FRACBITS;
    mo->momz -= FRACUNIT;
    mo->flags |= MF_DROPPED;
    mo->reactiontime = (P_Random() & 3) + 2;
}
