othello_get_rgbmap (int idx, int color)
{
	static guchar rgbbuf[3*OTHELLO_CELL_SIZE*OTHELLO_CELL_SIZE];
	int fg, bg, i;
	char *colors;
	colors = othello_colors;
	fg = (idx == OTHELLO_WP ? 0xee << 16 : 0xee);
	if (color == BLACK) colors += 3;
	for(i=0, bg=0;i<3;i++)
	{ int col = colors[i]; if (col<0) col += 256; bg += col * (1 << (16-8*i));}
	rgbmap_ball_shadow_gen(OTHELLO_CELL_SIZE, rgbbuf, fg, bg, 17.0, 30.0, 3);
	return rgbbuf;
}
