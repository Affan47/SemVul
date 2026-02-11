gdata_upload_stream_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
	GDataUploadStreamPrivate *priv = GDATA_UPLOAD_STREAM (object)->priv;

	switch (property_id) {
		case PROP_SERVICE:
			priv->service = g_value_dup_object (value);
			priv->session = _gdata_service_get_session (priv->service);
			break;
		case PROP_AUTHORIZATION_DOMAIN:
			priv->authorization_domain = g_value_dup_object (value);
			break;
		case PROP_METHOD:
			priv->method = g_value_dup_string (value);
			break;
		case PROP_UPLOAD_URI:
			priv->upload_uri = g_value_dup_string (value);
			break;
		case PROP_ENTRY:
			priv->entry = g_value_dup_object (value);
			break;
		case PROP_SLUG:
			priv->slug = g_value_dup_string (value);
			break;
		case PROP_CONTENT_TYPE:
			priv->content_type = g_value_dup_string (value);
			break;
		case PROP_CONTENT_LENGTH:
			priv->content_length = g_value_get_int64 (value);
			break;
		case PROP_CANCELLABLE:

			priv->cancellable = g_value_dup_object (value);
			break;
		default:

			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}
