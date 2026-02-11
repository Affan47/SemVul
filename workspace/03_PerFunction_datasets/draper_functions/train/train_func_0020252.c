ThingCount(int type, int tid)
{
    int count;
    int searcher;
    mobj_t *mobj;
    mobjtype_t moType;
    thinker_t *think;

    if (!(type + tid))
    {
        return;
    }
    moType = TranslateThingType[type];
    count = 0;
    searcher = -1;
    if (tid)
    {
        while ((mobj = P_FindMobjFromTID(tid, &searcher)) != NULL)
        {
            if (type == 0)
            {
                count++;
            }
            else if (moType == mobj->type)
            {
                if (mobj->flags & MF_COUNTKILL && mobj->health <= 0)
                {
                    continue;
                }
                count++;
            }
        }
    }
    else
    {
        for (think = thinkercap.next; think != &thinkercap;
             think = think->next)
        {
            if (think->function != P_MobjThinker)
            {
                continue;
            }
            mobj = (mobj_t *) think;
            if (mobj->type != moType)
            {
                continue;
            }
            if (mobj->flags & MF_COUNTKILL && mobj->health <= 0)
            {
                continue;
            }
            count++;
        }
    }
    Push(count);
}
