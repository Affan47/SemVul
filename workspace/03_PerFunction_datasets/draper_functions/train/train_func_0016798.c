A_KSpiritRoam(mobj_t * actor)
{
    if (actor->health-- <= 0)
    {
        S_StartSound(actor, SFX_SPIRIT_DIE);
        P_SetMobjState(actor, S_KSPIRIT_DEATH1);
    }
    else
    {
        if (actor->special1.m)
        {
            A_KSpiritSeeker(actor, actor->args[0] * ANG1,
                            actor->args[0] * ANG1 * 2);
        }
        A_KSpiritWeave(actor);
        if (P_Random() < 50)
        {
            S_StartSound(NULL, SFX_SPIRIT_ACTIVE);
        }
    }
}
