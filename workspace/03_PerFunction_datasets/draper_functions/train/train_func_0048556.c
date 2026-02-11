gd_textlayout(textspan_t * span, char **fontpath)
{
    char *err, *fontlist, *fontname;
    double fontsize;
    int brect[8];
    gdFTStringExtra strex;
    PostscriptAlias *pA;

    fontname = span->font->name;
    fontsize = span->font->size;

    strex.fontpath = NULL;
    strex.flags = gdFTEX_RETURNFONTPATHNAME | gdFTEX_RESOLUTION;
    strex.hdpi = strex.vdpi = POINTS_PER_INCH;

    if (strstr(fontname, "/"))
	strex.flags |= gdFTEX_FONTPATHNAME;
    else
	strex.flags |= gdFTEX_FONTCONFIG;

    span->size.x = 0.0;
    span->size.y = 0.0;
    span->yoffset_layout = 0.0;

    span->layout = NULL;
    span->free_layout = NULL;

    span->yoffset_centerline = 0.1 * fontsize;

    if (fontname) {
	if (fontsize <= FONTSIZE_MUCH_TOO_SMALL) {
	    return TRUE;
	} else if (fontsize <= FONTSIZE_TOO_SMALL) {


	    fontsize = FONTSIZE_TOO_SMALL;
	}

#ifdef HAVE_GD_FONTCONFIG
	gdFTUseFontConfig(1);
	pA = span->font->postscript_alias;
	if (pA)
	    fontlist = gd_psfontResolve (pA);
	else
	    fontlist = fontname;
#else
	fontlist = gd_alternate_fontlist(fontname);
#endif

	err = gdImageStringFTEx(NULL, brect, -1, fontlist,
				fontsize, 0, 0, 0, span->str, &strex);

	if (err) {
	    agerr(AGERR,"%s\n", err);
	    return FALSE;
	}

	if (fontpath)
	    *fontpath = strex.fontpath;
	else
	    free (strex.fontpath);

	if (span->str && span->str[0]) {

	    span->size.x = (double) (brect[4] - brect[0]);


	    span->size.y = (int)(fontsize * 1.2);
	}
    }
    return TRUE;
}
