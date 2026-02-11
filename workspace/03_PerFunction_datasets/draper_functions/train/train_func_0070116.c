wordtris_getmove (Pos *pos, int x, int y, GtkboardEventType type, Player to_play,
		byte **movp, int ** rmovep)
{
	static int rmove[7];
	int *rp = rmove;
	if (type != GTKBOARD_BUTTON_RELEASE)
		return 0;
	if (y != 0) return 0;
	if (wordtris_curx != x)
	{
		*rp++ = wordtris_curx;
		*rp++ = 0;
		*rp++ = 0;
		*rp++ = x;
		*rp++ = 0;
		*rp++ = RENDER_HIGHLIGHT1;
		*rp++ = -1;
		*rmovep = rmove;
	}
	wordtris_curx = x;
	return 0;
}
