_draw_rotated_rectangle (GogRenderer *rend, GogViewAllocation const *rect, gboolean fill, gboolean stroke, gboolean rotate_bg)
{
	GOStyle const *style;
	GOPath *path;
	gboolean narrow = (rect->w < 3.) || (rect->h < 3.);
	double o, o_2;

	g_return_if_fail (GOG_IS_RENDERER (rend));
	g_return_if_fail (GO_IS_STYLE (rend->cur_style));

	style = rend->cur_style;
	narrow |= !go_style_is_outline_visible (style);

	path = go_path_new ();
	go_path_set_options (path, GO_PATH_OPTIONS_SHARP);

	if (!narrow) {
		o = gog_renderer_line_size (rend, style->line.width);
		o_2 = o / 2.;
	} else
		o = o_2 = 0.;

	go_path_rectangle (path, 0., 0., rect->w - o, rect->h - o);

	cairo_save (rend->cairo);
	cairo_translate (rend->cairo, rect->x - o_2, rect->y - o_2);
	_draw_rotated_shape (rend, path, fill, stroke && !narrow, rotate_bg);
	cairo_restore (rend->cairo);

	go_path_free (path);
}
