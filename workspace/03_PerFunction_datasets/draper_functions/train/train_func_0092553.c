gog_area_series_get_interpolation_params (GogSeries const *series)
{
	GogAreaSeries *aseries = GOG_AREA_SERIES (series);
	g_return_val_if_fail (aseries, NULL);
	return aseries->interpolation_props;
}
