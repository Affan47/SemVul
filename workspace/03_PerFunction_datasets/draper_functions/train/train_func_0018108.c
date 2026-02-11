popup_draw_title(int sy, char *line, int flags)
{
	int w, h, sx;

	if ( flags & PF_TITLE_BIG ) {
		gr_set_font(FONT2);
	} else {
		gr_set_font(FONT1);
	}

	gr_get_string_size(&w, &h, line);
	sx = fl2i(Title_coords[gr_screen.res][4] - w/2.0f + 0.5f);

	popup_set_title_color(flags);
	gr_string(sx,sy,line);
}
