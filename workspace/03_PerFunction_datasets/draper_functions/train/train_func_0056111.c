flickr_service_set_property (GObject      *object,
			     guint         property_id,
			     const GValue *value,
			     GParamSpec   *pspec)
{
	FlickrService *self;

        self = FLICKR_SERVICE (object);

	switch (property_id) {
	case PROP_SERVER:
		self->priv->server = g_value_get_pointer (value);
		self->priv->consumer = oauth_consumer_copy (&flickr_consumer);
		self->priv->consumer->request_token_url = self->priv->server->request_token_url;
		self->priv->consumer->access_token_url = self->priv->server->access_token_url;
		self->priv->consumer->consumer_key = self->priv->server->consumer_key;
		self->priv->consumer->consumer_secret = self->priv->server->consumer_secret;
		g_object_set (self, "consumer", self->priv->consumer, NULL);
		break;
	default:
		break;
	}
}
