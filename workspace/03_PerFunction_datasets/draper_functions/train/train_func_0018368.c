sw_service_flickr_dispose (GObject *object)
{
  SwServiceFlickrPrivate *priv = SW_SERVICE_FLICKR (object)->priv;

  if (priv->proxy) {
    g_object_unref (priv->proxy);
    priv->proxy = NULL;
  }

  G_OBJECT_CLASS (sw_service_flickr_parent_class)->dispose (object);
}
