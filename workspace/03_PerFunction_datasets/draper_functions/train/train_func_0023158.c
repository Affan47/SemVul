sw_service_plurk_dispose (GObject *object)
{
  SwServicePlurkPrivate *priv = SW_SERVICE_PLURK (object)->priv;

  sw_online_remove_notify (online_notify, object);


  if (priv->proxy) {
    g_object_unref (priv->proxy);
    priv->proxy = NULL;
  }

  G_OBJECT_CLASS (sw_service_plurk_parent_class)->dispose (object);
}
