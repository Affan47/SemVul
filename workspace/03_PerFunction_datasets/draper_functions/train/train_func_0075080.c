gog_color_scale_set_property (GObject *obj, guint param_id,
		       GValue const *value, GParamSpec *pspec)
{
	GogColorScale *scale = GOG_COLOR_SCALE (obj);

	switch (param_id) {
	case COLOR_SCALE_PROP_HORIZONTAL:
		gog_color_scale_set_orientation (scale, g_value_get_boolean (value));
		break;
	case COLOR_SCALE_PROP_WIDTH:
		scale->width = g_value_get_double (value);
		break;
	case COLOR_SCALE_PROP_AXIS: {
		GogChart *chart = GOG_CHART (gog_object_get_parent (GOG_OBJECT (obj)));
		GSList *ptr;
		char const *buf = g_value_get_string (value);
		GogAxis *axis = NULL;
		for (ptr = gog_chart_get_axes (chart, GOG_AXIS_COLOR); ptr && ptr->data; ptr = ptr->next) {
			if (!strcmp (buf, gog_object_get_name (GOG_OBJECT (ptr->data)))) {
			    axis = GOG_AXIS (ptr->data);
				break;
			}
		}
		if (axis == NULL)
			for (ptr = gog_chart_get_axes (chart, GOG_AXIS_PSEUDO_3D); ptr && ptr->data; ptr = ptr->next) {
				if (!strcmp (buf, gog_object_get_name (GOG_OBJECT (ptr->data)))) {
					axis = GOG_AXIS (ptr->data);
					break;
				}
			}
		gog_color_scale_set_axis (scale, axis);
		break;
	}
	case COLOR_SCALE_PROP_TICK_SIZE_PTS:
		scale->tick_size = g_value_get_int (value);
		break;

	default: G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, param_id, pspec);
		 return;
	}

	gog_object_emit_changed (GOG_OBJECT (obj), TRUE);
}
