initfont(const char *fontstr) {
	char *def, **missing;
	int i, n;

	if(!fontstr || fontstr[0] == '\0')
		eprint("error, cannot load font: '%s'\n", fontstr);
	missing = NULL;
	dc.font.set = XCreateFontSet(dpy, fontstr, &missing, &n, &def);
	if(missing)
		XFreeStringList(missing);
	if(dc.font.set) {
		XFontSetExtents *font_extents;
		XFontStruct **xfonts;
		char **font_names;
		dc.font.ascent = dc.font.descent = 0;
		font_extents = XExtentsOfFontSet(dc.font.set);
		n = XFontsOfFontSet(dc.font.set, &xfonts, &font_names);
		for(i = 0, dc.font.ascent = 0, dc.font.descent = 0; i < n; i++) {
			if(dc.font.ascent < (*xfonts)->ascent)
				dc.font.ascent = (*xfonts)->ascent;
			if(dc.font.descent < (*xfonts)->descent)
				dc.font.descent = (*xfonts)->descent;
			xfonts++;
		}
	}
	else {
		if(!(dc.font.xfont = XLoadQueryFont(dpy, fontstr))
		&& !(dc.font.xfont = XLoadQueryFont(dpy, "fixed")))
			eprint("error, cannot load font: '%s'\n", fontstr);
		dc.font.ascent = dc.font.xfont->ascent;
		dc.font.descent = dc.font.xfont->descent;
	}
	dc.font.height = dc.font.ascent + dc.font.descent;
}
