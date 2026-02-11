gog_area_series_set_property (GObject *obj, guint param_id,
			    GValue const *value, GParamSpec *pspec)
{
	GogAreaSeries *series=  GOG_AREA_SERIES (obj);

	switch (param_id) {
	case SERIES_PROP_CLAMP0:
		gog_dataset_set_dim (series->interpolation_props, 0,
				     go_data_scalar_val_new (g_value_get_double (value)), NULL);
		break;
	case SERIES_PROP_CLAMP1:
		gog_dataset_set_dim (series->interpolation_props, 1,
				     go_data_scalar_val_new (g_value_get_double (value)), NULL);
		break;
	default: G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, param_id, pspec);
		 break;
	}
}
