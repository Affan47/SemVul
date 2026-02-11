ges_meta_container_register_meta (GESMetaContainer * container,
    GESMetaFlag flags, const gchar * meta_item, const GValue * value)
{
  g_return_val_if_fail (GES_IS_META_CONTAINER (container), FALSE);
  g_return_val_if_fail (meta_item != NULL, FALSE);

  if (!_register_meta (container, flags, meta_item, G_VALUE_TYPE (value)))
    return FALSE;

  return _set_value (container, meta_item, value);
}
