brasero_drive_properties_set_property (GObject *object,
				       guint property_id,
				       const GValue *value,
				       GParamSpec *pspec)
{
	BraseroDrivePropertiesPrivate *priv;
	BraseroBurnSession *session;

	priv = BRASERO_DRIVE_PROPERTIES_PRIVATE (object);

	switch (property_id) {
	case PROP_SESSION:


		session = g_value_get_object (value);
		priv->session = g_object_ref (session);

		brasero_drive_properties_update (BRASERO_DRIVE_PROPERTIES (object));
		priv->valid_sig = g_signal_connect (session,
						    "is-valid",
						    G_CALLBACK (brasero_drive_properties_is_valid_cb),
						    object);
		priv->output_sig = g_signal_connect (session,
						     "output-changed",
						     G_CALLBACK (brasero_drive_properties_output_changed_cb),
						     object);
		break;

	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
	}
}
