A_PoisonBagCheck(mobj_t * actor)
{
    if (!--actor->special1.i)
    {
        P_SetMobjState(actor, S_POISONCLOUD_X1);
    }
    else
    {
        return;
    }
}
