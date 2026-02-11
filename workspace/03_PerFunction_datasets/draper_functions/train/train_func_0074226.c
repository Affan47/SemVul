equal_movefilters(movefilter aamf1[MAX_FILTER_PLIES][MAX_FILTER_PLIES],
                  movefilter aamf2[MAX_FILTER_PLIES][MAX_FILTER_PLIES])
{

    int i;

    for (i = 0; i < MAX_FILTER_PLIES; ++i)
        if (!equal_movefilter(i, aamf1[i], aamf2[i]))
            return 0;

    return 1;

}
