RemoveAllThinkers(void)
{
    thinker_t *thinker;
    thinker_t *nextThinker;

    thinker = thinkercap.next;
    while (thinker != &thinkercap)
    {
        nextThinker = thinker->next;
        if (thinker->function == P_MobjThinker)
        {
            P_RemoveMobj((mobj_t *) thinker);
        }
        else
        {
            Z_Free(thinker);
        }
        thinker = nextThinker;
    }
    P_InitThinkers();
}
