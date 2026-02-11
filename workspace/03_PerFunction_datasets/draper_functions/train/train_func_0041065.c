photos_base_item_icon_updated (PhotosBaseItem *self, GIcon *icon)
{
  PhotosBaseItemPrivate *priv = self->priv;

  if (icon == NULL)
    return;

  g_clear_object (&priv->icon);
  priv->icon = g_object_ref (icon);
  photos_base_item_check_effects_and_update_info (self);
}
