nautilus_x_content_bar_set_property (GObject      *object,
				     guint         prop_id,
				     const GValue *value,
				     GParamSpec   *pspec)
{
	NautilusXContentBar *bar;

	bar = NAUTILUS_X_CONTENT_BAR (object);

	switch (prop_id) {
	case PROP_MOUNT:
		nautilus_x_content_bar_set_mount (bar, G_MOUNT (g_value_get_object (value)));
		break;
	case PROP_X_CONTENT_TYPES:
		nautilus_x_content_bar_set_x_content_types (bar, g_value_get_boxed (value));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
