ekiga_dialpad_set_property (GObject      *object,
                            guint         prop_id,
                            const GValue *value,
                            GParamSpec   *pspec)
{
  EkigaDialpad *dialpad = EKIGA_DIALPAD (object);

  switch (prop_id) {
    case PROP_ACCEL_GROUP:
      dialpad->priv->accel_group = GTK_ACCEL_GROUP (g_value_get_object (value));
      g_object_ref (dialpad->priv->accel_group);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
