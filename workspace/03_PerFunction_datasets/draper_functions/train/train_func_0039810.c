radial_drop_lines_can_add (GogObject const *parent)
{
	GogRTSeries *series = GOG_RT_SERIES (parent);
	return (   series->radial_drop_lines == NULL
		&& GOG_IS_PLOT_POLAR (gog_series_get_plot (GOG_SERIES (parent))));
}
