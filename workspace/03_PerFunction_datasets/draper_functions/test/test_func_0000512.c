contact_maybe_update_avatar_data (TpContact *self)
{
  if ((self->priv->has_features & CONTACT_FEATURE_FLAG_AVATAR_DATA) == 0 &&
      (self->priv->has_features & CONTACT_FEATURE_FLAG_AVATAR_TOKEN) != 0)
    {
      self->priv->has_features |= CONTACT_FEATURE_FLAG_AVATAR_DATA;
      contact_update_avatar_data (self);
    }
}
