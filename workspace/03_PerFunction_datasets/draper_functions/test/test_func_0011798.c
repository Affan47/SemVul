nautilus_column_get_property (GObject *object,
			      guint param_id,
			      GValue *value,
			      GParamSpec *pspec)
{
	NautilusColumn *column;

	column = NAUTILUS_COLUMN (object);

	switch (param_id) {
	case PROP_NAME :
		g_value_set_string (value, column->details->name);
		break;
	case PROP_ATTRIBUTE :
		g_value_set_string (value, g_quark_to_string (column->details->attribute));
		break;
	case PROP_ATTRIBUTE_Q :
		g_value_set_uint (value, column->details->attribute);
		break;
	case PROP_LABEL :
		g_value_set_string (value, column->details->label);
		break;
	case PROP_DESCRIPTION :
		g_value_set_string (value, column->details->description);
		break;
	case PROP_XALIGN :
		g_value_set_float (value, column->details->xalign);
		break;
	case PROP_DEFAULT_SORT_ORDER :
		g_value_set_enum (value, column->details->default_sort_order);
		break;
	default :
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
		break;
	}
}
