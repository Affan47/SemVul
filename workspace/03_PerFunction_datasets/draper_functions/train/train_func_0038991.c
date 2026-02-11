get_property (GObject *object, guint prop_id,
			  GValue *value, GParamSpec *pspec)
{
	NMAccessPointPrivate *priv = NM_AP_GET_PRIVATE (object);
	GArray * ssid;
	int len;
	int i;

	switch (prop_id) {
	case PROP_FLAGS:
		g_value_set_uint (value, priv->flags);
		break;
	case PROP_WPA_FLAGS:
		g_value_set_uint (value, priv->wpa_flags);
		break;
	case PROP_RSN_FLAGS:
		g_value_set_uint (value, priv->rsn_flags);
		break;
	case PROP_SSID:
		len = priv->ssid ? priv->ssid->len : 0;
		ssid = g_array_sized_new (FALSE, TRUE, sizeof (unsigned char), len);
		for (i = 0; i < len; i++)
			g_array_append_val (ssid, priv->ssid->data[i]);
		g_value_set_boxed (value, ssid);
		g_array_free (ssid, TRUE);
		break;
	case PROP_FREQUENCY:
		g_value_set_uint (value, priv->freq);
		break;
	case PROP_HW_ADDRESS:
		g_value_take_string (value, nm_utils_hwaddr_ntoa (&priv->address, ARPHRD_ETHER));
		break;
	case PROP_MODE:
		g_value_set_uint (value, priv->mode);
		break;
	case PROP_MAX_BITRATE:
		g_value_set_uint (value, priv->max_bitrate);
		break;
	case PROP_STRENGTH:
		g_value_set_schar (value, priv->strength);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
