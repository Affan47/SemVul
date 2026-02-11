draw_line(float x1, float y1, float x2, float y2, Uint32 color, int width)
{
	float rr, gg, bb;
	rr = (color & 0xff0000) >> 16;
	gg = (color & 0xff00) >> 8;
	bb = color & 0xff;

	if (!use_open_gl) {
		draw_line_sdl(Screen, x1, y1, x2, y2, rr, gg, bb, width);
	} else {
		draw_line_opengl(x1, y1, x2, y2, rr, gg, bb, width);
	}
}
