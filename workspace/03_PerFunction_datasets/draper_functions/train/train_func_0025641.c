clutter_actor_allocate_align_fill (ClutterActor           *self,
                                   const ClutterActorBox  *box,
                                   gdouble                 x_align,
                                   gdouble                 y_align,
                                   gboolean                x_fill,
                                   gboolean                y_fill,
                                   ClutterAllocationFlags  flags)
{
  ClutterActorPrivate *priv;
  ClutterActorBox allocation = CLUTTER_ACTOR_BOX_INIT_ZERO;
  gfloat x_offset, y_offset;
  gfloat available_width, available_height;
  gfloat child_width = 0.f, child_height = 0.f;

  g_return_if_fail (CLUTTER_IS_ACTOR (self));
  g_return_if_fail (box != NULL);
  g_return_if_fail (x_align >= 0.0 && x_align <= 1.0);
  g_return_if_fail (y_align >= 0.0 && y_align <= 1.0);

  priv = self->priv;

  clutter_actor_box_get_origin (box, &x_offset, &y_offset);
  clutter_actor_box_get_size (box, &available_width, &available_height);

  if (available_width < 0)
    available_width = 0;

  if (available_height < 0)
    available_height = 0;

  allocation.x1 = x_offset;
  allocation.y1 = y_offset;

  if (x_fill)
    child_width = available_width;

  if (y_fill)
    child_height = available_height;


  if (x_fill && y_fill)
    goto out;

  if (priv->request_mode == CLUTTER_REQUEST_HEIGHT_FOR_WIDTH)
    {
      gfloat min_width, natural_width;
      gfloat min_height, natural_height;

      if (!x_fill)
        {
          clutter_actor_get_preferred_width (self, available_height,
                                             &min_width,
                                             &natural_width);

          child_width = CLAMP (natural_width, min_width, available_width);
        }

      if (!y_fill)
        {
          clutter_actor_get_preferred_height (self, child_width,
                                              &min_height,
                                              &natural_height);

          child_height = CLAMP (natural_height, min_height, available_height);
        }
    }
  else
    {
      gfloat min_width, natural_width;
      gfloat min_height, natural_height;

      if (!y_fill)
        {
          clutter_actor_get_preferred_height (self, available_width,
                                              &min_height,
                                              &natural_height);

          child_height = CLAMP (natural_height, min_height, available_height);
        }

      if (!x_fill)
        {
          clutter_actor_get_preferred_width (self, child_height,
                                             &min_width,
                                             &natural_width);

          child_width = CLAMP (natural_width, min_width, available_width);
        }
    }


  if (priv->text_direction == CLUTTER_TEXT_DIRECTION_RTL)
    x_align = 1.0 - x_align;

  if (!x_fill)
    allocation.x1 += ((available_width - child_width) * x_align);

  if (!y_fill)
    allocation.y1 += ((available_height - child_height) * y_align);

out:

  allocation.x1 = floorf (allocation.x1);
  allocation.y1 = floorf (allocation.y1);
  allocation.x2 = ceilf (allocation.x1 + child_width);
  allocation.y2 = ceilf (allocation.y1 + child_height);

  clutter_actor_allocate (self, &allocation, flags);
}
