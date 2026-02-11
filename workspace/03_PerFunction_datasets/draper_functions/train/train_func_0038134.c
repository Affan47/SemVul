clutter_actor_get_margin (ClutterActor  *self,
                          ClutterMargin *margin)
{
  const ClutterLayoutInfo *info;

  g_return_if_fail (CLUTTER_IS_ACTOR (self));
  g_return_if_fail (margin != NULL);

  info = _clutter_actor_get_layout_info_or_defaults (self);

  *margin = info->margin;
}
