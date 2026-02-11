mx_icon_allocate (ClutterActor           *actor,
                  const ClutterActorBox  *box,
                  ClutterAllocationFlags  flags)
{
  MxIconPrivate *priv = MX_ICON (actor)->priv;

  CLUTTER_ACTOR_CLASS (mx_icon_parent_class)->allocate (actor, box, flags);

  if (priv->icon_texture)
    {
      MxPadding padding;
      ClutterActorBox child_box;

      mx_widget_get_padding (MX_WIDGET (actor), &padding);
      child_box.x1 = padding.left;
      child_box.y1 = padding.top;
      child_box.x2 = box->x2 - box->x1 - padding.right;
      child_box.y2 = box->y2 - box->y1 - padding.bottom;

      clutter_actor_allocate (priv->icon_texture, &child_box, flags);
    }
}
