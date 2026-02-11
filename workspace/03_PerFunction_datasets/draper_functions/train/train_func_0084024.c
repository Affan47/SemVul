mx_scroll_view_pick (ClutterActor       *actor,
                     const ClutterColor *color)
{
  MxScrollViewPrivate *priv = MX_SCROLL_VIEW (actor)->priv;
  ClutterActorBox      box;


  if (priv->child)
    {
      clutter_actor_get_allocation_box (priv->child, &box);
      cogl_clip_push_rectangle (0, 0, (box.x2 - box.x1), (box.y2 - box.y1));
    }

  CLUTTER_ACTOR_CLASS (mx_scroll_view_parent_class)->pick (actor, color);

  if (priv->child)
    cogl_clip_pop ();


  if (CLUTTER_ACTOR_IS_VISIBLE (priv->hscroll))
    clutter_actor_paint (priv->hscroll);
  if (CLUTTER_ACTOR_IS_VISIBLE (priv->vscroll))
    clutter_actor_paint (priv->vscroll);
}
