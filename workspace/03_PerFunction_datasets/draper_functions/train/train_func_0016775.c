e_map_get_property (GObject *object,
                    guint property_id,
                    GValue *value,
                    GParamSpec *pspec)
{
	EMap *map;

	map = E_MAP (object);

	switch (property_id) {
	case PROP_HADJUSTMENT:
		g_value_set_object (value, map->priv->hadjustment);
		break;
	case PROP_VADJUSTMENT:
		g_value_set_object (value, map->priv->vadjustment);
		break;
	case PROP_HSCROLL_POLICY:
		g_value_set_enum (value, map->priv->hscroll_policy);
		break;
	case PROP_VSCROLL_POLICY:
		g_value_set_enum (value, map->priv->vscroll_policy);
		break;

	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
