Term_text_gtk(int x, int y, int n, byte a, const char *s)
{
	term_data *td = (term_data*)(Term->data);
	cairo_rectangle_t r;

	char *s2;
	if (conv == NULL)
		s2 = process_control_chars(n, s);
	else
		s2 = latin1_to_utf8(n, s);

	init_cairo_rect(&r, (td->font.w * x), (td->font.h * y),  (td->font.w * n), td->font.h);
	draw_text(td->surface, &td->font, &td->actual, x, y, n, a, s2);
	invalidate_drawing_area(td->drawing_area, r);

	free(s2);
	return (0);
}
