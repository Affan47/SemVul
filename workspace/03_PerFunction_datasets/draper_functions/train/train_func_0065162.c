Streak_FindMultiGridContinuation(StreakVars *svars, POINT_TYPE *p)
{
    if (! svars->inside0)
    {
	VectorGrp last;

	if (svars->I0)
	{
	    last = svars->I0->currentVectorGrp;
	    (*(last->FreeInstanceVars))(svars->I0);
	}
	else
	    last = NULL;

	svars->I0 = Streak_FindMultiGridContinuation_1(svars->vf0, p, last);
	if (! svars->I0)
	    return 0;
    }

    if (! svars->inside1)
    {
	VectorGrp last;

	if (svars->I1)
	{
	    last = svars->I1->currentVectorGrp;
	    (*(last->FreeInstanceVars))(svars->I1);
	}
	else
	    last = NULL;

	svars->I1 = Streak_FindMultiGridContinuation_1(svars->vf1, p, last);
	if (! svars->I1)
	    return 0;
    }
    return 1;
}
