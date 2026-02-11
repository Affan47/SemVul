evd_web_transport_server_set_base_path (EvdWebTransportServer *self,
                                        const gchar           *base_path)
{
  g_return_if_fail (base_path != NULL);

  if (base_path[strlen (base_path) - 1] == '/')
    self->priv->base_path = g_strdup (base_path);
  else
    self->priv->base_path = g_strdup_printf ("%s/", base_path);

  self->priv->hs_base_path = g_strdup_printf ("%s%s",
                                              self->priv->base_path,
                                              HANDSHAKE_TOKEN_NAME);
  self->priv->lp_base_path = g_strdup_printf ("%s%s",
                                              self->priv->base_path,
                                              LONG_POLLING_TOKEN_NAME);
  self->priv->ws_base_path = g_strdup_printf ("%s%s",
                                              self->priv->base_path,
                                              WEB_SOCKET_TOKEN_NAME);

  evd_web_dir_set_alias (EVD_WEB_DIR (self), base_path);
}
