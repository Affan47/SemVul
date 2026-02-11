clutter_state_key_new (State       *state,
                       GObject     *object,
                       const gchar *property_name,
                       GParamSpec  *pspec,
                       guint        mode)
{
  ClutterStatePrivate *priv = state->clutter_state->priv;
  ClutterStateKey *state_key;
  GValue value = G_VALUE_INIT;

  state_key = g_slice_new0 (ClutterStateKey);

  state_key->target_state = state;
  state_key->object = object;
  state_key->property_name = g_intern_string (property_name);
  state_key->mode = mode;
  state_key->is_animatable = CLUTTER_IS_ANIMATABLE (object);

  state_key->alpha = clutter_alpha_new ();
  g_object_ref_sink (state_key->alpha);
  clutter_alpha_set_mode (state_key->alpha, mode);
  clutter_alpha_set_timeline (state_key->alpha, priv->slave_timeline);

  state_key->interval =
    g_object_new (CLUTTER_TYPE_INTERVAL,
                  "value-type", G_PARAM_SPEC_VALUE_TYPE (pspec),
                  NULL);
  g_object_ref_sink (state_key->interval);

  g_value_init (&value, G_PARAM_SPEC_VALUE_TYPE (pspec));
  clutter_interval_set_initial_value (state_key->interval, &value);
  clutter_interval_set_final_value (state_key->interval, &value);
  g_value_unset (&value);

  g_object_weak_ref (object, object_disappeared,
                     state_key->target_state->clutter_state);

  return state_key;
}
