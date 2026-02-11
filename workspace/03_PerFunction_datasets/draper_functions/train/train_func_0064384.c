gnome_canvas_pixbuf_set_property (GObject *object,
                                  guint param_id,
                                  const GValue *value,
                                  GParamSpec *pspec)
{
	GnomeCanvasItem *item;
	GnomeCanvasPixbuf *gcp;
	GnomeCanvasPixbufPrivate *priv;
	GdkPixbuf *pixbuf;

	g_return_if_fail (object != NULL);
	g_return_if_fail (GNOME_IS_CANVAS_PIXBUF (object));

	item = GNOME_CANVAS_ITEM (object);
	gcp = GNOME_CANVAS_PIXBUF (object);
	priv = gcp->priv;

	switch (param_id) {
	case PROP_PIXBUF:
		pixbuf = g_value_get_object (value);
		if (pixbuf != priv->pixbuf) {
			if (priv->pixbuf)
				g_object_unref (priv->pixbuf);

			priv->pixbuf = g_object_ref (pixbuf);
		}

		gnome_canvas_item_request_update (item);
		break;

	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
		break;
	}
}
