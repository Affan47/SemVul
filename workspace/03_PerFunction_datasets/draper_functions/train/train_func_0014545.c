nemo_mime_application_chooser_set_property (GObject *object,
						guint property_id,
						const GValue *value,
						GParamSpec *pspec)
{
	NemoMimeApplicationChooser *chooser = NEMO_MIME_APPLICATION_CHOOSER (object);

	switch (property_id) {
	case PROP_CONTENT_TYPE:
		chooser->details->content_type = g_value_dup_string (value);
		break;
	case PROP_FILES:
		chooser->details->files = g_value_get_pointer (value);
		break;
	case PROP_URI:
		chooser->details->uri = g_value_dup_string (value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
