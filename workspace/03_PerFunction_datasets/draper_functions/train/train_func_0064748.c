set_property (GObject *object, guint property_id,
              const GValue *value, GParamSpec *pspec)
{
	NMConnectivity *self = NM_CONNECTIVITY (object);
	NMConnectivityPrivate *priv = NM_CONNECTIVITY_GET_PRIVATE (self);

	switch (property_id) {
	case PROP_URI:
		g_free (priv->uri);
		priv->uri = get_non_empty_string_value (value);

#if WITH_CONCHECK
		if (priv->uri) {
			SoupURI *uri = soup_uri_new (priv->uri);

			if (!uri || !SOUP_URI_VALID_FOR_HTTP (uri)) {
				nm_log_err (LOGD_CONCHECK, "Invalid uri '%s' for connectivity check.", priv->uri);
				g_free (priv->uri);
				priv->uri = NULL;
			}
		}
#endif
		break;
	case PROP_INTERVAL:
		priv->interval = g_value_get_uint (value);
		break;
	case PROP_RESPONSE:
		g_free (priv->response);
		priv->response = get_non_empty_string_value (value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
