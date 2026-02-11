gdata_picasaweb_user_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec)
{
	GDataPicasaWebUserPrivate *priv = GDATA_PICASAWEB_USER (object)->priv;

	switch (property_id) {
		case PROP_USER:
			g_value_set_string (value, priv->user);
			break;
		case PROP_NICKNAME:
			g_value_set_string (value, priv->nickname);
			break;
		case PROP_QUOTA_LIMIT:
			g_value_set_int64 (value, priv->quota_limit);
			break;
		case PROP_QUOTA_CURRENT:
			g_value_set_int64 (value, priv->quota_current);
			break;
		case PROP_MAX_PHOTOS_PER_ALBUM:
			g_value_set_int (value, priv->max_photos_per_album);
			break;
		case PROP_THUMBNAIL_URI:
			g_value_set_string (value, priv->thumbnail_uri);
			break;
		default:

			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}
