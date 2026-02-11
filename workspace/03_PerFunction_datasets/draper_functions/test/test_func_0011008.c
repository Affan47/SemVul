A_Sor2DthLoop(mobj_t * actor)
{
    if (--actor->special1.i)
    {
        P_SetMobjState(actor, S_SOR2_DIE4);
    }
}
