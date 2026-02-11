non_zero_winding_sharp(fz_gel *gel, int y,
	fz_bbox clip, fz_pixmap *dst, unsigned char *color)
{
	int winding = 0;
	int x = 0;
	int i;
	for (i = 0; i < gel->alen; i++)
	{
		if (!winding && (winding + gel->active[i]->ydir))
			x = gel->active[i]->x;
		if (winding && !(winding + gel->active[i]->ydir))
			blit_sharp(x, gel->active[i]->x, y, clip, dst, color);
		winding += gel->active[i]->ydir;
	}
}
