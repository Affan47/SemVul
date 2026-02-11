mx_tooltip_allocate (ClutterActor          *self,
                     const ClutterActorBox *box,
                     ClutterAllocationFlags flags)
{
  MxTooltipPrivate *priv = MX_TOOLTIP (self)->priv;
  ClutterActorBox child_box, arrow_box;
  gfloat arrow_height, arrow_width;
  ClutterActor *border_image, *arrow_image;
  MxPadding padding;

  CLUTTER_ACTOR_CLASS (mx_tooltip_parent_class)->allocate (self,
                                                           box,
                                                           flags);

  mx_widget_get_padding (MX_WIDGET (self), &padding);

  arrow_image = mx_widget_get_background_image (MX_WIDGET (self));

  if (arrow_image && !priv->actor_below)
    {
      clutter_actor_get_preferred_height (arrow_image, -1, NULL, &arrow_height);
      clutter_actor_get_preferred_width (arrow_image, -1, NULL, &arrow_width);

      arrow_box.x1 = (float)(priv->arrow_offset) - (int)(arrow_width / 2);
      arrow_box.y1 = 0;
      arrow_box.x2 = arrow_box.x1 + arrow_width;
      arrow_box.y2 = arrow_box.y1 + arrow_height;

      clutter_actor_allocate (arrow_image, &arrow_box, flags);
    }
  else
    {
      arrow_height = 0;
      arrow_width = 0;
    }

  child_box.x1 = child_box.y1 = 0;
  child_box.x2 = (box->x2 - box->x1);
  child_box.y2 = (box->y2 - box->y1);


  child_box.y1 += arrow_height;

  border_image = mx_widget_get_border_image (MX_WIDGET (self));
  if (border_image)
    clutter_actor_allocate (border_image, &child_box, flags);

  if (priv->label)
    {

      child_box.y1 += padding.top;
      child_box.x1 += padding.left;
      child_box.x2 -= padding.right;
      child_box.y2 -= padding.bottom;

      clutter_actor_allocate (priv->label, &child_box, flags);
    }
}
