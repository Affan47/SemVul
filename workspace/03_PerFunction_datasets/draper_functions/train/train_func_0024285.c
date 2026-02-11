getXLFDName(dpy, nonxlfdname)
Display *dpy;
String nonxlfdname;
{
    XFontStruct *font;
    Atom fontprop;
    String name;

    TRACE(("getXLFDName(%s)\n", nonxlfdname));
    font = CachedLoadQueryFontByName(dpy, nonxlfdname);
    if (font == NULL) {
	DPRINT(("getXLFDName(%s):CachedLoadQueryFontByName() failed\n",
		nonxlfdname));
	return NULL;
    }
    if (!XGetFontProperty(font, XA_FONT, (unsigned long *)&fontprop)) {

	DPRINT(("getXLFDName(%s): can't get FONT property\n",
		nonxlfdname));
	CachedFreeFont(dpy, font);
	return NULL;
    }

    CachedFreeFont(dpy, font);
    name = CachedGetAtomName(dpy, fontprop);
    TRACE(("\tgot %s\n", name));
    return (*name == '-' || *name == '+') ? name : NULL;
}
