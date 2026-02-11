cairo_DrawRectangle (GpGraphics *graphics, GpPen *pen, float x, float y, float width, float height)
{

	if (gdip_cairo_pen_width_needs_adjustment (pen)) {
		x -= 1.0f;
		y -= 1.0f;
	}
	gdip_cairo_rectangle (graphics, x, y, width, height, TRUE);
	return stroke_graphics_with_pen (graphics, pen);
}
