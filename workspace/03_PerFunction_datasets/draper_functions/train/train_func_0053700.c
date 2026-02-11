add_or_remove_flatten_effect (ClutterActor *self)
{
  ClutterActorPrivate *priv = self->priv;


  if (needs_flatten_effect (self))
    {
      if (priv->flatten_effect == NULL)
        {
          ClutterActorMeta *actor_meta;
          gint priority;

          priv->flatten_effect = _clutter_flatten_effect_new ();


          g_object_ref_sink (priv->flatten_effect);


          actor_meta = CLUTTER_ACTOR_META (priv->flatten_effect);
          priority = CLUTTER_ACTOR_META_PRIORITY_INTERNAL_HIGH;
          _clutter_actor_meta_set_priority (actor_meta, priority);


          _clutter_actor_add_effect_internal (self, priv->flatten_effect);
        }
    }
  else
    {
      if (priv->flatten_effect != NULL)
        {


          _clutter_actor_remove_effect_internal (self, priv->flatten_effect);
          g_clear_object (&priv->flatten_effect);
        }
    }
}
