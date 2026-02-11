set_property (GObject *object, guint prop_id,
              const GValue *value, GParamSpec *pspec)
{
	NMSettingBondPrivate *priv = NM_SETTING_BOND_GET_PRIVATE (object);
	GHashTable *new_hash;

	switch (prop_id) {
	case PROP_INTERFACE_NAME:
		priv->interface_name = g_value_dup_string (value);
		break;
	case PROP_OPTIONS:

		g_hash_table_remove_all (priv->options);
		new_hash = g_value_get_boxed (value);
		if (new_hash)
			g_hash_table_foreach (new_hash, copy_hash, priv->options);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
