dnb_get_pixmap (int idx, int color)
{
	int bg, i;
	char *colors = dnb_colors;
	static char pixbuf[DNB_CELL_SIZE * (DNB_CELL_SIZE+1)];
	if (color == BLACK) colors += 3;
	for(i=0, bg=0;i<3;i++)
	{ int col = colors[i]; if (col<0) col += 256; bg += col * (1 << (16-8*i));}
	if (idx == DNB_DOT)
		return pixmap_ball_gen (DNB_CELL_SIZE, pixbuf, 0x101010, bg, 8, 30);
	if (idx == DNB_VERT) return dnb_vertical_24_xpm;
	if (idx == DNB_HOR) return dnb_horizontal_24_xpm;
	if (idx == DNB_RED) return dnb_red_24_xpm;
	if (idx == DNB_BLUE) return dnb_blue_24_xpm;
	return NULL;
}
