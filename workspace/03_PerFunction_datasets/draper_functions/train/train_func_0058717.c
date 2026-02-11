clutter_actor_get_pango_context (ClutterActor *self)
{
  ClutterActorPrivate *priv;

  g_return_val_if_fail (CLUTTER_IS_ACTOR (self), NULL);

  priv = self->priv;

  if (priv->pango_context != NULL)
    return priv->pango_context;

  priv->pango_context = _clutter_context_get_pango_context ();
  g_object_ref (priv->pango_context);

  return priv->pango_context;
}
