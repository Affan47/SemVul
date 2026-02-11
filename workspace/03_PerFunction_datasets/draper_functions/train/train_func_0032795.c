get_custom_mouse_limits (int *pw, int *ph, int *pdx, int *pdy, int dbl)
{
	int delay1, delay2;
	int w, h, dx, dy, dbl1, dbl2, y1, y2;

	w = diwlastword_total - diwfirstword_total;
	dx = diwfirstword_total - visible_left_border;

	y2 = plflastline_total;
	if (y2 > last_planes_vpos)
		y2 = last_planes_vpos;
	y1 = plffirstline_total;
	if (first_planes_vpos > y1)
		y1 = first_planes_vpos;
	if (minfirstline > y1)
		y1 = minfirstline;

	h = y2 - y1;
	dy = y1 - minfirstline;

	if (*pw > 0)
		w = *pw;

	w = xshift (w, res_shift);

	if (*ph > 0)
		h = *ph;

	delay1 = (firstword_bplcon1 & 0x0f) | ((firstword_bplcon1 & 0x0c00) >> 6);
	delay2 = ((firstword_bplcon1 >> 4) & 0x0f) | (((firstword_bplcon1 >> 4) & 0x0c00) >> 6);


	dx = xshift (dx, res_shift);

	dbl2 = dbl1 = currprefs.gfx_vresolution;
	if ((doublescan > 0 || interlace_seen > 0) && !dbl) {
		dbl1--;
		dbl2--;
	}
	if (interlace_seen > 0)
		dbl2++;
	if (interlace_seen <= 0 && dbl)
		dbl2--;
	h = xshift (h, dbl1);
	dy = xshift (dy, dbl2);

	if (w < 1)
		w = 1;
	if (h < 1)
		h = 1;
	if (dx < 0)
		dx = 0;
	if (dy < 0)
		dy = 0;
	*pw = w; *ph = h;
	*pdx = dx; *pdy = dy;
}
