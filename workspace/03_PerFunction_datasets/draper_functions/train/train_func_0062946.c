hiq_get_pixmap (int idx, int color)
{
	int bg, i, fg, rad, grad;
	char *colors;
	static char pixbuf[HIQ_CELL_SIZE * (HIQ_CELL_SIZE+1)];
	if (idx == HIQ_UNUSED) return grey_square_54_xpm;
	colors = hiq_colors;
	if (color == BLACK) colors += 3;
	for(i=0, bg=0;i<3;i++)
	{ int col = colors[i]; if (col<0) col += 256; bg += col * (1 << (16-8*i));}
	fg = (idx == HIQ_RP ? 0xff << 16 : 0xd0d0d0);
	rad = (idx == HIQ_RP ? 16 : 18);
	grad = (idx == HIQ_RP ? 24 : 36);
	return pixmap_ball_gen(54, pixbuf, fg, bg, rad, grad);
}
