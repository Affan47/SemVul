role_series_element_allocate (GogObject *series)
{
	GogSeriesClass *klass = GOG_SERIES_GET_CLASS (series);
	GType type = klass->series_element_type;
	GogObject *gse;

	if (type == 0)
		return NULL;

	gse = g_object_new (type, NULL);
	if (gse != NULL)
		gog_series_element_set_index (GOG_SERIES_ELEMENT (gse),
			gog_series_get_valid_element_index (GOG_SERIES (series), -1, 0));
	return gse;
}
