go_style_force_auto (GOStyle *style)
{
	g_return_if_fail (GO_IS_STYLE (style));

	if (style->marker.mark != NULL)
		g_object_unref (style->marker.mark);
	style->marker.mark = go_marker_new ();
	style->marker.auto_shape =
	style->marker.auto_outline_color =
	style->marker.auto_fill_color =
	style->line.auto_dash =
	style->line.auto_color =
	style->line.auto_fore =
	style->line.auto_width =
	style->fill.auto_type =
	style->fill.auto_fore =
	style->fill.auto_back =
	style->fill.auto_pattern =
	style->fill.gradient.auto_dir =
	style->fill.gradient.auto_brightness =
	style->font.auto_scale =
	style->font.auto_font =
	style->font.auto_color =
	style->text_layout.auto_angle = TRUE;
}
