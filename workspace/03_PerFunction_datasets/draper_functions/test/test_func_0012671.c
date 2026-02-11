cairo_DrawRectanglesI (GpGraphics *graphics, GpPen *pen, GDIPCONST GpRect *rects, int count)
{
	BOOL draw = FALSE;
	BOOL adjust = gdip_cairo_pen_width_needs_adjustment (pen);
	int i;

	for (i = 0; i < count; i++) {
		int x = rects [i].X;
		int y = rects [i].Y;
		int w = rects [i].Width;
		int h = rects [i].Height;


		if ((w < 0) || (h < 0))
			continue;


		if (adjust) {
			x -= 1;
			y -= 1;
		}

		gdip_cairo_rectangle (graphics, x, y, w, h, TRUE);
		draw = TRUE;
	}

	if (!draw)
		return Ok;

	return stroke_graphics_with_pen (graphics, pen);
}
