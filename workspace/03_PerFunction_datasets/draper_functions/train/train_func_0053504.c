cache_print_set (FcFontSet *set, FcStrSet *dirs, const FcChar8 *base_name, FcBool verbose)
{
    FcChar8	    *dir;
    const FcChar8   *base;
    int		    n;
    int		    ndir = 0;
    FcStrList	    *list;

    list = FcStrListCreate (dirs);
    if (!list)
	goto bail2;

    while ((dir = FcStrListNext (list)))
    {
	base = file_base_name (base_name, dir);
	if (!write_string (stdout, base))
	    goto bail3;
	if (PUTC (' ', stdout) == EOF)
	    goto bail3;
	if (!write_int (stdout, 0))
	    goto bail3;
        if (PUTC (' ', stdout) == EOF)
	    goto bail3;
	if (!write_string (stdout, FC_FONT_FILE_DIR))
	    goto bail3;
	if (PUTC ('\n', stdout) == EOF)
	    goto bail3;
	ndir++;
    }

    for (n = 0; n < set->nfont; n++)
    {
	FcPattern   *font = set->fonts[n];
	FcChar8 *s;

	s = FcPatternFormat (font, (const FcChar8 *) "%{=fccat}\n");
	if (s)
	{
	    printf ("%s", s);
	    FcStrFree (s);
	}
    }
    if (verbose && !set->nfont && !ndir)
	printf ("<empty>\n");

    FcStrListDone (list);

    return FcTrue;

bail3:
    FcStrListDone (list);
bail2:
    return FcFalse;
}
