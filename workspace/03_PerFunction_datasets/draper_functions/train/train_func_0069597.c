clutter_actor_set_content (ClutterActor   *self,
                           ClutterContent *content)
{
  ClutterActorPrivate *priv;

  g_return_if_fail (CLUTTER_IS_ACTOR (self));
  g_return_if_fail (content == NULL || CLUTTER_IS_CONTENT (content));

  priv = self->priv;

  if (priv->content != NULL)
    {
      _clutter_content_detached (priv->content, self);
      g_clear_object (&priv->content);
    }

  priv->content = content;

  if (priv->content != NULL)
    {
      g_object_ref (priv->content);
      _clutter_content_attached (priv->content, self);
    }


  clutter_actor_queue_redraw (self);

  g_object_notify_by_pspec (G_OBJECT (self), obj_props[PROP_CONTENT]);


  if (priv->content_gravity != CLUTTER_CONTENT_GRAVITY_RESIZE_FILL)
    g_object_notify_by_pspec (G_OBJECT (self), obj_props[PROP_CONTENT_BOX]);
}
