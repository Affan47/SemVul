gdata_youtube_state_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec)
{
	GDataYouTubeStatePrivate *priv = GDATA_YOUTUBE_STATE (object)->priv;

	switch (property_id) {
		case PROP_NAME:
			g_value_set_string (value, priv->name);
			break;
		case PROP_REASON_CODE:
			g_value_set_string (value, priv->reason_code);
			break;
		case PROP_HELP_URI:
			g_value_set_string (value, priv->help_uri);
			break;
		case PROP_MESSAGE:
			g_value_set_string (value, priv->message);
			break;
		default:

			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}
