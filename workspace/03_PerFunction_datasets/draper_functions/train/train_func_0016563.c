A_Feathers(mobj_t * actor)
{
    int i;
    int count;
    mobj_t *mo;

    if (actor->health > 0)
    {
        count = P_Random() < 32 ? 2 : 1;
    }
    else
    {
        count = 5 + (P_Random() & 3);
    }
    for (i = 0; i < count; i++)
    {
        mo = P_SpawnMobj(actor->x, actor->y, actor->z + 20 * FRACUNIT,
                         MT_FEATHER);
        mo->target = actor;
        mo->momx = (P_Random() - P_Random()) << 8;
        mo->momy = (P_Random() - P_Random()) << 8;
        mo->momz = FRACUNIT + (P_Random() << 9);
        P_SetMobjState(mo, S_FEATHER1 + (P_Random() & 7));
    }
}
