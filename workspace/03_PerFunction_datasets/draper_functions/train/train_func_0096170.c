almanah_tag_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
	AlmanahTagPrivate *priv = ALMANAH_TAG (object)->priv;

	switch (property_id) {
		case PROP_TAG:
			if (priv->tag)
				g_free (priv->tag);
			priv->tag = g_strdup (g_value_get_string (value));
			if (PANGO_IS_LAYOUT (priv->layout)) {
				pango_layout_set_text (priv->layout, priv->tag, -1);
				gtk_widget_queue_resize (GTK_WIDGET (object));
			}
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}
