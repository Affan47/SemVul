gdata_picasaweb_query_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec)
{
	GDataPicasaWebQueryPrivate *priv = GDATA_PICASAWEB_QUERY (object)->priv;

	switch (property_id) {
		case PROP_VISIBILITY:
			g_value_set_int (value, priv->visibility);
			break;
		case PROP_THUMBNAIL_SIZE:
			g_value_set_string (value, priv->thumbnail_size);
			break;
		case PROP_IMAGE_SIZE:
			g_value_set_string (value, priv->image_size);
			break;
		case PROP_TAG:
			g_value_set_string (value, priv->tag);
			break;
		case PROP_LOCATION:
			g_value_set_string (value, priv->location);
			break;
		default:

			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}
