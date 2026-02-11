gog_trend_line_get_property (GObject *obj, guint param_id,
			 GValue *value, GParamSpec *pspec)
{
	switch (param_id) {
	case TREND_LINE_PROP_HAS_LEGEND :
		g_value_set_boolean (value, GPOINTER_TO_INT (g_object_get_data (obj, "has-legend")));
		break;

	default: G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, param_id, pspec);
		 break;
	}
}
