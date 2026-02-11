tryCharSet(dpy, cset, extfont, namelist, numlist, func)
Display *dpy;
KICharSet *cset;
KICharSetFont *extfont;
FSFontName *namelist;
Cardinal numlist;
XFontStruct *(*func)();
{
    KICharSetSpec *specs;
    Cardinal i;
    XFontStruct *font;

    for (i = 0, specs = cset->specs; i < cset->num_specs; i++, specs++) {
	font = (*func)(dpy, specs->pattern, namelist, numlist);
	if (font != NULL) {
	    extfont->charset = specs->pattern;
	    extfont->cldata = specs->cldata;
	    extfont->font = font;
	    return True;
	}
    }
    return False;
}
