clutter_actor_real_paint (ClutterActor *actor)
{
  ClutterActorPrivate *priv = actor->priv;
  ClutterActor *iter;

  for (iter = priv->first_child;
       iter != NULL;
       iter = iter->priv->next_sibling)
    {
      CLUTTER_NOTE (PAINT, "Painting %s, child of %s, at { %.2f, %.2f - %.2f x %.2f }",
                    _clutter_actor_get_debug_name (iter),
                    _clutter_actor_get_debug_name (actor),
                    iter->priv->allocation.x1,
                    iter->priv->allocation.y1,
                    iter->priv->allocation.x2 - iter->priv->allocation.x1,
                    iter->priv->allocation.y2 - iter->priv->allocation.y1);

      clutter_actor_paint (iter);
    }
}
