FlocaleGetFontSet(
	Display *dpy, char *fontname, char *encoding, char *module)
{
	static int mc_errors = 0;
	FlocaleFont *flf = NULL;
	XFontSet fontset = NULL;
	char **ml;
	int mc,i;
	char *ds;
	XFontSetExtents *fset_extents;
	char *fn, *hints = NULL, *fn_fixed = NULL;

	hints = GetQuotedString(fontname, &fn, "/", NULL, NULL, NULL);
	if (*fn == '\0')
	{
		free(fn);
		fn = fn_fixed = mb_fallback_font;
	}
	else if (!(fn_fixed = FlocaleFixNameForFontSet(dpy, fn, module)))
	{
		if (fn != NULL && fn != mb_fallback_font)
		{
			free(fn);
		}
		return NULL;
	}
	if (!(fontset = XCreateFontSet(dpy, fn_fixed, &ml, &mc, &ds)))
	{
		if (fn_fixed && fn_fixed != fn)
		{
			free(fn_fixed);
		}
		if (fn != NULL && fn != mb_fallback_font)
		{
			free(fn);
		}
		return NULL;
	}

	if (mc > 0)
	{
		if (mc_errors <= FLOCALE_NUMBER_MISS_CSET_ERR_MSG)
		{
			mc_errors++;
			fprintf(stderr,
				"[%s][FlocaleGetFontSet]: (%s)"
				" Missing font charsets:\n",
				(module)? module: "fvwmlibs", fontname);
			for (i = 0; i < mc; i++)
			{
				fprintf(stderr, "%s", ml[i]);
				if (i < mc - 1)
					fprintf(stderr, ", ");
			}
			fprintf(stderr, "\n");
			if (mc_errors == FLOCALE_NUMBER_MISS_CSET_ERR_MSG)
			{
				fprintf(stderr,
					"[%s][FlocaleGetFontSet]: No more"
					" missing charset reportings\n",
					(module)? module: "fvwmlibs");
			}
		}
		XFreeStringList(ml);
	}

	flf = (FlocaleFont *)safemalloc(sizeof(FlocaleFont));
	memset(flf, '\0', sizeof(FlocaleFont));
	flf->count = 1;
	flf->fontset = fontset;
	FlocaleCharsetSetFlocaleCharset(dpy, flf, hints, encoding, module);
	fset_extents = XExtentsOfFontSet(fontset);
	flf->height = fset_extents->max_ink_extent.height;
	flf->ascent = - fset_extents->max_ink_extent.y;
	flf->descent = fset_extents->max_ink_extent.height +
		fset_extents->max_ink_extent.y;
	flf->max_char_width = fset_extents->max_ink_extent.width;
	if (fn_fixed && fn_fixed != fn)
	{
		free(fn_fixed);
	}
	if (fn != NULL && fn != mb_fallback_font)
	{
		free(fn);
	}

	return flf;
}
