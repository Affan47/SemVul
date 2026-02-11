gog_renderer_stroke_serie (GogRenderer *renderer,
			   GOPath const *path)
{
	GOStyle const *style;
	GOPathOptions line_options;
	double width;

	g_return_if_fail (GOG_IS_RENDERER (renderer));
	g_return_if_fail (renderer->cur_style != NULL);
	g_return_if_fail (GO_IS_PATH (path));

        style = renderer->cur_style;
	line_options = go_path_get_options (path);
	width = _grc_line_size (renderer,
				style->line.width,
				line_options & GO_PATH_OPTIONS_SNAP_WIDTH);

	if (go_style_is_line_visible (style)) {
		path_interpret (renderer, path, width);
		emit_line (renderer, FALSE, go_path_get_options (path));
	}
}
