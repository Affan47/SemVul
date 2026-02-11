_fetch_extra_data (FrogrController *self, gboolean force)
{
  FrogrControllerPrivate *priv = NULL;

  g_return_if_fail(FROGR_IS_CONTROLLER (self));

  if (!frogr_controller_is_connected (self))
    return;

  priv = FROGR_CONTROLLER_GET_PRIVATE (self);


  if (force)
    _invalidate_extra_data (self);


  if (force || !priv->photosets_fetched)
    _fetch_photosets (self);
  if (force || !priv->groups_fetched)
    _fetch_groups (self);
  if (force || !priv->tags_fetched)
    _fetch_tags (self);
}
