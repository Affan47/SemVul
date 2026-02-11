role_series_allocate (GogObject *plot)
{
	GogPlotClass *klass = GOG_PLOT_GET_CLASS (plot);
	GType type = klass->series_type;

	if (type == 0)
		type = GOG_TYPE_SERIES;
	return g_object_new (type, NULL);
}
