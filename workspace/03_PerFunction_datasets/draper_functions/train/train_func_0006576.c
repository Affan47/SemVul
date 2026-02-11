gtk_builder_object_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	g_return_if_fail (GTK_IS_BUILDER_OBJECT (object));

	GtkBuilderObjectPrivate* priv;
	priv = GTK_BUILDER_OBJECT_PRIVATE(object);

	switch (prop_id)
	{
	case PROP_UI_FILE:
		g_value_set_string (value, priv->uifile);
		break;
	case PROP_TOPLEVEL_WIDGET_NAME:
		g_value_set_string (value, priv->toplevel_widget_name);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
