clutter_animator_property_get_ease_in (ClutterAnimator *animator,
                                       GObject         *object,
                                       const gchar     *property_name)
{
  ClutterAnimatorKey  key, *initial_key;
  GList              *initial;

  g_return_val_if_fail (CLUTTER_IS_ANIMATOR (animator), FALSE);
  g_return_val_if_fail (G_IS_OBJECT (object), FALSE);
  g_return_val_if_fail (property_name, FALSE);

  key.object        = object;
  key.property_name = g_intern_string (property_name);
  initial = g_list_find_custom (animator->priv->score, &key,
                                sort_actor_prop_func);
  if (initial != NULL)
    {
      initial_key = initial->data;

      return initial_key->ease_in;
    }

  return FALSE;
}
