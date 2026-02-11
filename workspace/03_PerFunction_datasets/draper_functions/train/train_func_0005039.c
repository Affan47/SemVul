clutter_animation_unbind_property (ClutterAnimation *animation,
                                   const gchar      *property_name)
{
  ClutterAnimationPrivate *priv;

  g_return_if_fail (CLUTTER_IS_ANIMATION (animation));
  g_return_if_fail (property_name != NULL);

  priv = animation->priv;

  if (!clutter_animation_has_property (animation, property_name))
    {
      g_warning ("Cannot unbind property '%s': the animation has "
                 "no bound property with that name",
                 property_name);
      return;
    }

  g_hash_table_remove (priv->properties, property_name);
}
