mx_button_get_icon_size (MxButton *button)
{
  g_return_val_if_fail (MX_IS_BUTTON (button), 0);

  return button->priv->icon_size ?
    button->priv->icon_size : button->priv->style_icon_size;
}
