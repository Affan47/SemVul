online_notify (gboolean online, gpointer user_data)
{
  SwServiceMySpace *service = (SwServiceMySpace *) user_data;
  SwServiceMySpacePrivate *priv = service->priv;

  if (online) {
    sw_keyfob_oauth ((OAuthProxy *)priv->proxy, got_tokens_cb, service);
  } else {
    g_free (priv->user_id);
    priv->user_id = NULL;

    g_free (priv->image_url);
    priv->image_url = NULL;

    sw_service_emit_capabilities_changed ((SwService *)service,
                                          get_dynamic_caps ((SwService *)service));
  }
}
