brasero_burn_progress_set_property (GObject *object,
				    guint property_id,
				    const GValue *value,
				    GParamSpec *pspec)
{
	BraseroBurnProgress *progress;

	progress = BRASERO_BURN_PROGRESS (object);
	switch (property_id) {
	case PROP_SHOW_INFO:
		if (!g_value_get_boolean (value)) {
			if (progress->priv->speed_table) {
				gtk_widget_destroy (progress->priv->speed_table);
				progress->priv->speed_table = NULL;
				progress->priv->speed_label = NULL;
				progress->priv->speed = NULL;
			}
		}
		else if (progress->priv->speed_table)
			brasero_burn_progress_create_info (progress);
		break;

	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
	}
}
