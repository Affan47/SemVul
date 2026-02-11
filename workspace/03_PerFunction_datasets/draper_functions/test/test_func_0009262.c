clutter_animator_property_set_ease_in (ClutterAnimator *animator,
                                       GObject         *object,
                                       const gchar     *property_name,
                                       gboolean         ease_in)
{
  ClutterAnimatorKey  key, *initial_key;
  GList              *initial;

  g_return_if_fail (CLUTTER_IS_ANIMATOR (animator));
  g_return_if_fail (G_IS_OBJECT (object));
  g_return_if_fail (property_name);

  key.object        = object;
  key.property_name = g_intern_string (property_name);
  initial = g_list_find_custom (animator->priv->score, &key,
                                sort_actor_prop_func);
  if (initial)
    {
      initial_key = initial->data;
      initial_key->ease_in = ease_in;
    }
  else
    g_warning ("The animator has no object of type '%s' with a "
               "property named '%s'",
               G_OBJECT_TYPE_NAME (object),
               property_name);
}
