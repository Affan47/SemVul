gog_series_set_XL_dim (GogSeries *series, GogMSDimType ms_type, GOData *val, GError **err)
{
	int dim;
	g_return_if_fail (series !=NULL);
	dim = gog_series_map_XL_dim (series, ms_type);
	if (dim >= -1) {
		gog_series_set_dim (series, dim, val, err);
		return;
	}
	g_object_unref (val);
}
