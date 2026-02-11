statusicon_start_blinking (StatusIcon *icon,
                           const char *icon_name)
{
  g_return_if_fail (icon != NULL);

  icon->priv->blink_image = g_strdup (icon_name);
  if (icon->priv->blink_id == -1)
    icon->priv->blink_id = g_timeout_add_seconds (1, statusicon_blink_cb, icon);
}
