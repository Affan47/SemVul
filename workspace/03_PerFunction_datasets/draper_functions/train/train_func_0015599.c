cheese_flash_set_property (GObject      *object,
                           guint         prop_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
  CheeseFlashPrivate *priv = CHEESE_FLASH (object)->priv;

  switch (prop_id)
  {
    case PROP_PARENT: {
      GObject *object;
      object = g_value_get_object (value);
      if (object != NULL)
        priv->parent = g_object_ref (object);
      else
        priv->parent = NULL;
    }
    break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
