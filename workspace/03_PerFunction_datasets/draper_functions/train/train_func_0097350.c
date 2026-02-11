_credentials_updated_func (gpointer data, gpointer userdata)
{
  SwService *service = SW_SERVICE (data);
  SwServiceFacebookPrivate *priv = SW_SERVICE_FACEBOOK (service)->priv;

  online_notify (FALSE, service);

  if (priv->pic_square){
     g_free (priv->pic_square);
     priv->pic_square = NULL;
  }
  online_notify (TRUE, service);

  sw_service_emit_user_changed (service);
  sw_service_emit_capabilities_changed ((SwService *)service,
                                        get_dynamic_caps (service));
}
