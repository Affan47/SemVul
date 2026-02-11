get_random_mon(int level) {
    objectlink *mon;
    int i, monnr;


    if (!nrofmon || !first_mon_info)
        return (object *)NULL;

    if (!level) {

        monnr = RANDOM()%nrofmon;

        for (mon = first_mon_info, i = 0; mon; mon = mon->next, i++)
            if (i == monnr)
                break;

        if (!mon) {
            LOG(llevError, "get_random_mon: Didn't find a monster when we should have\n");
            return NULL;
        }
        return mon->ob;
    }


    for (mon = first_mon_info, i = 0; mon; mon = mon->next)
        if (mon->ob->level >= level)
            i++;

    if (i == 0) {
        LOG(llevError, "get_random_mon() couldn't return monster for level %d\n", level);
        return NULL;
    }

    monnr = RANDOM()%i;
    for (mon = first_mon_info; mon; mon = mon->next)
        if (mon->ob->level >= level && monnr-- == 0)
            return mon->ob;

    LOG(llevError, "get_random_mon(): didn't find a monster when we should have\n");
    return NULL;
}
