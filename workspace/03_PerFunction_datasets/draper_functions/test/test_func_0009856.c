frogr_controller_fetch_tags_if_needed (FrogrController *self)
{
  FrogrControllerPrivate *priv = NULL;

  g_return_if_fail(FROGR_IS_CONTROLLER (self));

  priv = FROGR_CONTROLLER_GET_PRIVATE (self);
  if (!priv->fetching_tags && !priv->tags_fetched)
    _fetch_tags (self);
}
