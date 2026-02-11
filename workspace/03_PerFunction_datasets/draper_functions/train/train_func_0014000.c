web_service_set_property (GObject      *object,
			  guint         property_id,
			  const GValue *value,
			  GParamSpec   *pspec)
{
	WebService *self = WEB_SERVICE (object);

	switch (property_id) {
	case PROP_SERVICE_NAME:
		_g_strset (&self->priv->service_name, g_value_get_string (value));
		break;
	case PROP_SERVICE_ADDRESS:
		_g_strset (&self->priv->service_address, g_value_get_string (value));
		break;
	case PROP_SERVICE_PROTOCOL:
		_g_strset (&self->priv->service_protocol, g_value_get_string (value));
		break;
	case PROP_ACCOUNT_TYPE:
		self->priv->account_type = g_value_get_gtype (value);
		break;
	case PROP_CANCELLABLE:
		_g_object_unref (self->priv->cancellable);
		self->priv->cancellable = g_value_dup_object (value);
		break;
	case PROP_BROWSER:
		self->priv->browser = g_value_get_pointer (value);
		break;
	case PROP_DIALOG:
		self->priv->dialog = g_value_get_pointer (value);
		break;
	default:
		break;
	}
}
