STlib_updateMultIcon
( st_multicon_t*	mi,
  boolean		refresh )
{
    int			w;
    int			h;
    int			x;
    int			y;

    if (*mi->on
	&& (mi->oldinum != *mi->inum || refresh)
	&& (*mi->inum!=-1))
    {
	if (mi->oldinum != -1)
	{
	    x = mi->x - SHORT(mi->p[mi->oldinum]->leftoffset);
	    y = mi->y - SHORT(mi->p[mi->oldinum]->topoffset);
	    w = SHORT(mi->p[mi->oldinum]->width);
	    h = SHORT(mi->p[mi->oldinum]->height);

	    if (y - ST_Y < 0)
		I_Error("updateMultIcon: y - ST_Y < 0");

	    V_CopyRect(x, y-ST_Y, st_backing_screen, w, h, x, y);
	}
	V_DrawPatch(mi->x, mi->y, mi->p[*mi->inum]);
	mi->oldinum = *mi->inum;
    }
}
