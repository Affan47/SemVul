mx_button_set_icon_name (MxButton    *button,
                         const gchar *icon_name)
{
  MxButtonPrivate *priv;

  g_return_if_fail (MX_IS_BUTTON (button));

  priv = button->priv;

  g_free (priv->icon_name);
  priv->icon_name = g_strdup (icon_name);

  mx_icon_set_icon_name (MX_ICON (priv->icon), icon_name ?
                         icon_name : priv->style_icon_name);
  mx_button_update_contents (button);

  g_object_notify (G_OBJECT (button), "icon-name");
}
