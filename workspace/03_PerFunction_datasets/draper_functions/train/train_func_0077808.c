FcFontSetDeserialize (const FcFontSet *set)
{
    int i;
    FcFontSet *new = FcFontSetCreate ();

    if (!new)
	return NULL;
    for (i = 0; i < set->nfont; i++)
    {
	if (!FcFontSetAdd (new, FcPatternDuplicate (FcFontSetFont (set, i))))
	    goto bail;
    }

    return new;
bail:
    FcFontSetDestroy (new);

    return NULL;
}
