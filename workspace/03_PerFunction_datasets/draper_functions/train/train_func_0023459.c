mx_scroll_bar_pick (ClutterActor       *actor,
                    const ClutterColor *pick_color)
{
  MxScrollBarPrivate *priv = MX_SCROLL_BAR (actor)->priv;

  CLUTTER_ACTOR_CLASS (mx_scroll_bar_parent_class)->pick (actor, pick_color);

  clutter_actor_paint (priv->bw_stepper);
  clutter_actor_paint (priv->fw_stepper);
  clutter_actor_paint (priv->trough);

  if (priv->handle && priv->adjustment)
    clutter_actor_paint (priv->handle);
}
