clutter_drag_action_real_drag_motion (ClutterDragAction *action,
                                      ClutterActor      *actor,
                                      gfloat             delta_x,
                                      gfloat             delta_y)
{
  ClutterActor *drag_handle;
  gfloat x, y;

  if (action->priv->drag_handle != NULL)
    drag_handle = action->priv->drag_handle;
  else
    drag_handle = actor;

  clutter_actor_get_position (drag_handle, &x, &y);

  x += delta_x;
  y += delta_y;

  if (action->priv->drag_area_set)
    {
      ClutterRect *drag_area = &action->priv->drag_area;

      x = CLAMP (x, drag_area->origin.x, drag_area->origin.x + drag_area->size.width);
      y = CLAMP (y, drag_area->origin.y, drag_area->origin.y + drag_area->size.height);
    }

  clutter_actor_set_position (drag_handle, x, y);
}
