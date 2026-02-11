rb_segmented_bar_set_property (GObject *object,
			       guint param_id,
			       const GValue *value,
			       GParamSpec *pspec)
{
	RBSegmentedBarPrivate *priv;
	priv = RB_SEGMENTED_BAR_GET_PRIVATE (RB_SEGMENTED_BAR (object));

	switch (param_id) {
	    case PROP_SHOW_REFLECTION:
		priv->reflect = g_value_get_boolean (value);
		break;
	    case PROP_SHOW_LABELS:
		priv->show_labels = g_value_get_boolean (value);
		break;
	    case PROP_BAR_HEIGHT:
		priv->bar_height = g_value_get_uint (value);
		break;
	    default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
		break;
	}
}
