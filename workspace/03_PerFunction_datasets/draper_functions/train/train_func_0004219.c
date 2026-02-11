e_map_set_property (GObject *object,
                    guint property_id,
                    const GValue *value,
                    GParamSpec *pspec)
{
	EMap *map;

	map = E_MAP (object);

	switch (property_id) {
	case PROP_HADJUSTMENT:
		e_map_set_hadjustment (map, g_value_get_object (value));
		break;
	case PROP_VADJUSTMENT:
		e_map_set_vadjustment (map, g_value_get_object (value));
		break;
	case PROP_HSCROLL_POLICY:
		map->priv->hscroll_policy = g_value_get_enum (value);
		gtk_widget_queue_resize (GTK_WIDGET (map));
		break;
	case PROP_VSCROLL_POLICY:
		map->priv->vscroll_policy = g_value_get_enum (value);
		gtk_widget_queue_resize (GTK_WIDGET (map));
		break;

	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
