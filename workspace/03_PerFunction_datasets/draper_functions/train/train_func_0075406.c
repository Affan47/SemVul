FcNameUnparseEscaped (FcPattern *pat, FcBool escape)
{
    FcStrBuf		    buf;
    FcChar8		    buf_static[8192];
    int			    i;
    FcPatternElt	    *e;

    FcStrBufInit (&buf, buf_static, sizeof (buf_static));
    e = FcPatternObjectFindElt (pat, FC_FAMILY_OBJECT);
    if (e)
    {
        if (!FcNameUnparseValueList (&buf, FcPatternEltValues(e), escape ? (FcChar8 *) FC_ESCAPE_FIXED : 0))
	    goto bail0;
    }
    e = FcPatternObjectFindElt (pat, FC_SIZE_OBJECT);
    if (e)
    {
	if (!FcNameUnparseString (&buf, (FcChar8 *) "-", 0))
	    goto bail0;
	if (!FcNameUnparseValueList (&buf, FcPatternEltValues(e), escape ? (FcChar8 *) FC_ESCAPE_FIXED : 0))
	    goto bail0;
    }
    for (i = 0; i < NUM_OBJECT_TYPES; i++)
    {
	FcObject id = i + 1;
	const FcObjectType	    *o;
	o = &FcObjects[i];
	if (!strcmp (o->object, FC_FAMILY) ||
	    !strcmp (o->object, FC_SIZE))
	    continue;

	e = FcPatternObjectFindElt (pat, id);
	if (e)
	{
	    if (!FcNameUnparseString (&buf, (FcChar8 *) ":", 0))
		goto bail0;
	    if (!FcNameUnparseString (&buf, (FcChar8 *) o->object, escape ? (FcChar8 *) FC_ESCAPE_VARIABLE : 0))
		goto bail0;
	    if (!FcNameUnparseString (&buf, (FcChar8 *) "=", 0))
		goto bail0;
	    if (!FcNameUnparseValueList (&buf, FcPatternEltValues(e), escape ?
					 (FcChar8 *) FC_ESCAPE_VARIABLE : 0))
		goto bail0;
	}
    }
    return FcStrBufDone (&buf);
bail0:
    FcStrBufDestroy (&buf);
    return 0;
}
