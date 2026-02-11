magic_map_background(xchar x, xchar y, int show)
{
    int glyph = back_to_glyph(x,y);
    struct rm *lev = &levl[x][y];


    if (!cansee(x,y) && !lev->waslit) {

	if (lev->typ == ROOM && glyph == cmap_to_glyph(S_room))
	    glyph = cmap_to_glyph(S_stone);
	else if (lev->typ == CORR && glyph == cmap_to_glyph(S_litcorr))
	    glyph = cmap_to_glyph(S_corr);
    }
    if (level.flags.hero_memory)
	lev->glyph = glyph;
    if (show) show_glyph(x,y, glyph);
}
