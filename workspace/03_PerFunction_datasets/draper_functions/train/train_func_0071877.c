glyph_intern(char const *glyphname) {
    int i, j, k, c;
    glyph *gp;

    i = -1;
    j = lenof(ps_glyphs_alphabetic);
    while (j-i > 1) {
	k = (i + j) / 2;
	c = strcmp(glyphname, ps_glyphs_alphabetic[k]);

	if (c == 0)
	    return k;
	else if (c < 0)
	    j = k;
	else
	    i = k;
    }

    if (extrabyname == NULL)
	extrabyname = newtree234(glyphcmp);
    gp = find234(extrabyname, (void *)glyphname, glyphcmp_search);
    if (gp) {
	k = *gp;
    } else {
	extraglyphs = sresize(extraglyphs, nextglyph, char const *);
	k = nextglyph++;
	extraglyphs[k - lenof(ps_glyphs_alphabetic)] = dupstr(glyphname);
	gp = snew(glyph);
	*gp = k;
	add234(extrabyname, gp);
    }
    return k;
}
