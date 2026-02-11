clutter_actor_clear_actions (ClutterActor *self)
{
  g_return_if_fail (CLUTTER_IS_ACTOR (self));

  if (self->priv->actions == NULL)
    return;

  _clutter_meta_group_clear_metas_no_internal (self->priv->actions);
}
