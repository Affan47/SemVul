gog_color_polar_series_init_style (GogStyledObject *gso, GOStyle *style)
{
	series_parent_klass->init_style (gso, style);
	style->fill.type = GO_STYLE_FILL_NONE;
	if (style->line.auto_dash)
		style->line.dash_type = GO_LINE_NONE;
}
