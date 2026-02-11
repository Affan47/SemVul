get_dynamic_caps (SwService *service)
{
  SwServiceVimeoPrivate *priv = SW_SERVICE_VIMEO (service)->priv;

  static const char *configured_caps[] = {
    IS_CONFIGURED,
    NULL
  };

  static const char *authorized_caps[] = {
    IS_CONFIGURED,
    CREDENTIALS_VALID,
    NULL
  };

  static const char *no_caps[] = { NULL };

  if (priv->username != NULL)
    return authorized_caps;
  else if (priv->configured)
    return configured_caps;
  else
    return no_caps;
}
