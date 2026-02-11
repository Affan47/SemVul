cheese_widget_get_property (GObject *object, guint prop_id,
                            GValue *value, GParamSpec *pspec)
{
  CheeseWidgetPrivate *priv = ((CheeseWidget *) object)->priv;

  g_return_if_fail (CHEESE_IS_WIDGET (object));

  switch (prop_id)
  {
    case PROP_STATE:
      g_value_set_enum (value, priv->state);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
