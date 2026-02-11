A_ImpExplode(mobj_t * actor)
{
    mobj_t *mo;

    mo = P_SpawnMobj(actor->x, actor->y, actor->z, MT_IMPCHUNK1);
    mo->momx = (P_Random() - P_Random()) << 10;
    mo->momy = (P_Random() - P_Random()) << 10;
    mo->momz = 9 * FRACUNIT;
    mo = P_SpawnMobj(actor->x, actor->y, actor->z, MT_IMPCHUNK2);
    mo->momx = (P_Random() - P_Random()) << 10;
    mo->momy = (P_Random() - P_Random()) << 10;
    mo->momz = 9 * FRACUNIT;
    if (actor->special1.i == 666)
    {
        P_SetMobjState(actor, S_IMP_XCRASH1);
    }
}
