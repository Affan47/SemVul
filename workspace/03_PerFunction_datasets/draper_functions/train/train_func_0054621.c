ctlr_add_fg(int baddr, unsigned char color)
{
	if (!appres.m3279)
		return;
	if ((color & 0xf0) != 0xf0)
		color = 0;
	if (ea_buf[baddr].fg != color) {
		if (SELECTED(baddr))
			unselect(baddr, 1);
		ONE_CHANGED(baddr);
		ea_buf[baddr].fg = color;
	}
}
