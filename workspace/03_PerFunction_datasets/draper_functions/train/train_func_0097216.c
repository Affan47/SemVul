glade_widget_action_set_property (GObject * object, guint prop_id,
                                  const GValue * value, GParamSpec * pspec)
{
  GladeWidgetAction *action = GLADE_WIDGET_ACTION (object);

  g_return_if_fail (GLADE_IS_WIDGET_ACTION (object));

  switch (prop_id)
    {
      case PROP_CLASS:
        action->priv->klass = g_value_get_pointer (value);
        break;
      case PROP_SENSITIVE:
        glade_widget_action_set_sensitive (action, g_value_get_boolean (value));
        break;
      case PROP_VISIBLE:
        glade_widget_action_set_visible (action, g_value_get_boolean (value));
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}
