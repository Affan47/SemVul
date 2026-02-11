gog_label_get_property (GObject *obj, guint param_id,
                        GValue *value, GParamSpec *pspec)
{
	GogLabel *label = GOG_LABEL (obj);

	switch (param_id) {
	case LABEL_PROP_JUSTIFICATION:
		switch (label->justification) {
		case GO_JUSTIFY_CENTER:
			g_value_set_string (value, "center");
			break;
		case GO_JUSTIFY_LEFT:
			g_value_set_string (value, "left");
			break;
		case GO_JUSTIFY_RIGHT:
			g_value_set_string (value, "right");
			break;
		case GO_JUSTIFY_FILL:
			g_value_set_string (value, "fill");
			break;
		}
		break;

	default: G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, param_id, pspec);
		 break;
	}
}
