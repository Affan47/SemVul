mx_window_x11_button_release (MxWindowX11 *self)
{
  MxWindowX11Private *priv = self->priv;

  if (priv->is_moving != -1)
    {
      clutter_ungrab_pointer_for_device (priv->is_moving);
      clutter_set_motion_events_enabled (TRUE);
      priv->is_moving = -1;
    }
}
