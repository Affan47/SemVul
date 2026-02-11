ajFeattableGetScorerange(const AjPFeattable thys,
                                float *minscore, float *maxscore)
{
    AjBool ret = ajFalse;
    float curmin = 0.0;
    float curmax = 0.0;
    AjIList iter;
    AjPFeature gf = NULL;

    if(!thys)
        return 0;

    *minscore = 0.0;
    *maxscore = 0.0;

    iter = ajListIterNewread(thys->Features);
    while(!ajListIterDone(iter))
    {
        gf = ajListIterGet(iter);

        curmin = 0.0;
        curmax = 0.0;

        if(ajFeatGetScorerange(gf, &curmin, &curmax))
        {
            if(curmin < *minscore)
            {
                ret = ajTrue;
                *minscore = curmin;
            }
            if(curmax > *maxscore)
            {
                ret = ajTrue;
                *maxscore = curmax;
            }
        }
    }

    ajListIterDel(&iter);

    return ret;
}
