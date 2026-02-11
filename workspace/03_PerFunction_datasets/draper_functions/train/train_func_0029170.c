gschem_action_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
  GschemAction *action = GSCHEM_ACTION (object);

  switch(property_id) {
    case PROP_MULTIKEY_ACCEL:
      g_free (action->multikey_accel);
      action->multikey_accel = g_strdup (g_value_get_string (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
  }
}
