go_component_set_property (GObject *obj, guint param_id,
		       GValue const *value, GParamSpec *pspec)
{
	GOComponent *component = GO_COMPONENT (obj);
	char const *str;

	switch (param_id) {
	case COMPONENT_PROP_MIME_TYPE:
		g_free (component->mime_type);
		str = g_value_get_string (value);
		if (str == NULL)
			break;
		component->mime_type = g_strdup (str);
		if (GO_COMPONENT_GET_CLASS (obj)->mime_type_set != NULL)
			GO_COMPONENT_GET_CLASS (obj)->mime_type_set (component);
		break;
	case COMPONENT_PROP_WIDTH:
		component->width = g_value_get_double (value);
		break;
	case COMPONENT_PROP_ASCENT:
		component->ascent = g_value_get_double (value);
		break;
	case COMPONENT_PROP_DESCENT:
		component->descent = g_value_get_double (value);
		break;
	case COMPONENT_PROP_INLINE:
		component->priv->is_inline = g_value_get_boolean (value);
		break;
	default: G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, param_id, pspec);
		 return;
	}
}
