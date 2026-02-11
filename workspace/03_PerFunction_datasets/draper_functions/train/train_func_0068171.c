A_ImpXDeath2(mobj_t * actor)
{
    actor->flags &= ~MF_NOGRAVITY;
    if (actor->z <= actor->floorz)
    {
        P_SetMobjState(actor, S_IMP_CRASH1);
    }
}
