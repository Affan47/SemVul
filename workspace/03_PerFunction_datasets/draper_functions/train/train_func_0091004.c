glyph_at(x, y)
    xchar x,y;
{
    if(x < 0 || y < 0 || x >= COLNO || y >= ROWNO)
	return cmap_to_glyph(S_room);
    return gbuf[y][x].glyph;
}
