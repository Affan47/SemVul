rb_search_entry_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	RBSearchEntry *entry = RB_SEARCH_ENTRY (object);

	switch (prop_id) {
	case PROP_EXPLICIT_MODE:
		entry->priv->explicit_mode = g_value_get_boolean (value);
		gtk_widget_set_visible (entry->priv->button, entry->priv->explicit_mode == TRUE);
		rb_search_entry_update_icons (entry);
		break;
	case PROP_HAS_POPUP:
		entry->priv->has_popup = g_value_get_boolean (value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
