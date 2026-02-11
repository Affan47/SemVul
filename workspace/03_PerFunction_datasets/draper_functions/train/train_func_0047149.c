gx_wipezbuf(int noshadow)
{
	UINT8  *zptr;
	int w, h;
	register int ecx;

	w = Machine->visible_area.max_x - Machine->visible_area.min_x + 1;
	h = Machine->visible_area.max_y - Machine->visible_area.min_y + 1;

	zptr = gx_objzbuf;
	ecx = h;
	do { memset(zptr, -1, w); zptr += GX_ZBUFW; } while (--ecx);

	if (!noshadow)
	{
		zptr = gx_shdzbuf;
		w <<= 1;
		ecx = h;
		do { memset(zptr, -1, w); zptr += (GX_ZBUFW<<1); } while (--ecx);
	}
}
