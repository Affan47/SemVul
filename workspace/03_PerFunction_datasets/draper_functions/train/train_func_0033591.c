st_button_fake_release (StButton *button)
{
  if (button->priv->pressed)
    st_button_release (button, button->priv->pressed, 0);

  if (button->priv->grabbed)
    {
      button->priv->grabbed = 0;
      clutter_ungrab_pointer ();
    }
}
