frogr_controller_revoke_authorization (FrogrController *self)
{
  FrogrControllerPrivate *priv = NULL;

  g_return_if_fail(FROGR_IS_CONTROLLER (self));

  priv = FROGR_CONTROLLER_GET_PRIVATE (self);


  fsp_session_set_token (priv->session, NULL);
  fsp_session_set_token_secret (priv->session, NULL);
  _set_active_account (self, NULL);
}
