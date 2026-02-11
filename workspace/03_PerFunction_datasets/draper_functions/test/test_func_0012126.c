gog_probability_plot_dataset_dim_changed (GogDataset *set, int dim_i)
{
	GogProbabilityPlot const *plot = GOG_PROBABILITY_PLOT (set);
	GParamSpec *spec;
	GType prop_type;

	if (!plot->shape_params[dim_i].prop_name)
		return;
	spec = g_object_class_find_property (G_OBJECT_GET_CLASS (plot->dist), plot->shape_params[dim_i].prop_name);
	prop_type = G_PARAM_SPEC_VALUE_TYPE (spec);
	switch G_TYPE_FUNDAMENTAL (prop_type) {
	case G_TYPE_DOUBLE: {
		GValue value = {0};
		g_value_init (&value, G_TYPE_DOUBLE);
		if (plot->shape_params[dim_i].elem->data)
			g_value_set_double (&value, go_data_get_scalar_value (plot->shape_params[dim_i].elem->data));
		else
			g_param_value_set_default (spec, &value);
		g_param_value_validate (spec, &value);
		g_object_set_property (G_OBJECT (plot->dist), plot->shape_params[dim_i].prop_name, &value);
		g_value_unset (&value);
		break;
	}
	default:
		g_critical ("Unsupported property type. Please report.");
		break;
	}
	if (plot->base.series)
		gog_object_request_update (GOG_OBJECT (plot->base.series->data));
	gog_object_request_update (GOG_OBJECT (set));
}
