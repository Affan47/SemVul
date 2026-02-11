clutter_actor_set_name (ClutterActor *self,
			const gchar  *name)
{
  g_return_if_fail (CLUTTER_IS_ACTOR (self));

  g_free (self->priv->name);
  self->priv->name = g_strdup (name);

  g_object_notify_by_pspec (G_OBJECT (self), obj_props[PROP_NAME]);
}
