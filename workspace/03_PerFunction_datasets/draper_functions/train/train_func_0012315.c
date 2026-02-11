gn_combo_history_set_property (GObject  *object, guint prop_id, const GValue *value,
			       GParamSpec *spec)
{
	GnComboHistory *history;

	g_return_if_fail (GN_IS_COMBO_HISTORY (object));

	history = GN_COMBO_HISTORY (object);

	switch (prop_id) {
	case PROP_COMBO:
		history->priv->combo = g_value_get_pointer (value);
		break;
	case PROP_ID:
		if (history->priv->id) g_free (history->priv->id);
		history->priv->id = g_value_dup_string (value);
		break;
	case PROP_MAX_HISTORY:
		history->priv->max_history = g_value_get_uint (value);
		break;
	default:
		break;
	}
}
