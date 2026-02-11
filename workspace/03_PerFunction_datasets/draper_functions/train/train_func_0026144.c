FcListPatternEqual (FcPattern	*p1,
		    FcPattern	*p2,
		    FcObjectSet	*os)
{
    int		    i;
    FcPatternElt    *e1, *e2;

    for (i = 0; i < os->nobject; i++)
    {
	e1 = FcPatternObjectFindElt (p1, FcObjectFromName (os->objects[i]));
	e2 = FcPatternObjectFindElt (p2, FcObjectFromName (os->objects[i]));
	if (!e1 && !e2)
	    continue;
	if (!e1 || !e2)
	    return FcFalse;
	if (!FcListValueListEqual (FcPatternEltValues(e1),
				   FcPatternEltValues(e2)))
	    return FcFalse;
    }
    return FcTrue;
}
