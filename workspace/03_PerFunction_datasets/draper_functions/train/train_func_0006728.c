tgui_copy_rect(struct tridentfb_par *par,
			   u32 x1, u32 y1, u32 x2, u32 y2, u32 w, u32 h)
{
	int flags = 0;
	u16 x1_tmp, x2_tmp, y1_tmp, y2_tmp;

	if ((x1 < x2) && (y1 == y2)) {
		flags |= 0x0200;
		x1_tmp = x1 + w - 1;
		x2_tmp = x2 + w - 1;
	} else {
		x1_tmp = x1;
		x2_tmp = x2;
	}

	if (y1 < y2) {
		flags |= 0x0100;
		y1_tmp = y1 + h - 1;
		y2_tmp = y2 + h - 1;
	} else {
		y1_tmp = y1;
		y2_tmp = y2;
	}

	writemmr(par, DRAWFL, 0x4 | flags);
	t_outb(par, ROP_S, 0x2127);
	writemmr(par, OLDSRC, point(x1_tmp, y1_tmp));
	writemmr(par, OLDDST, point(x2_tmp, y2_tmp));
	writemmr(par, OLDDIM, point(w - 1, h - 1));
	t_outb(par, 1, OLDCMD);
}
