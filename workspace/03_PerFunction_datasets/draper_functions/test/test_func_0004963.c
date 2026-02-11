trough_button_press_event_cb (ClutterActor       *actor,
                              ClutterButtonEvent *event,
                              StScrollBar        *self)
{
  g_return_val_if_fail (self, FALSE);

  if (event->button != 1)
    return FALSE;

  if (self->priv->adjustment == NULL)
    return FALSE;

  self->priv->move_x = event->x;
  self->priv->move_y = event->y;
  self->priv->paging_direction = NONE;
  self->priv->paging_event_no = 0;
  trough_paging_cb (self);

  return TRUE;
}
