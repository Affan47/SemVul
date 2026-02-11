gog_xyz_series_init_style (GogStyledObject *gso, GOStyle *style)
{
	series_parent_klass->init_style (gso, style);
	if (GOG_IS_MATRIX_PLOT (GOG_SERIES (gso)->plot) && style->line.auto_dash)
		style->line.dash_type = GO_LINE_NONE;
}
