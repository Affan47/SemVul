geany_menu_button_action_set_property(GObject *object, guint prop_id,
												  const GValue *value, GParamSpec *pspec)
{
	switch (prop_id)
	{
	case PROP_TOOLTIP_ARROW:
	{
		GeanyMenubuttonActionPrivate *priv = GEANY_MENU_BUTTON_ACTION_GET_PRIVATE(object);
		g_free(priv->tooltip_arrow);
		priv->tooltip_arrow = g_value_dup_string(value);
		break;
	}
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}
