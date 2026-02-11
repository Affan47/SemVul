mx_action_get_property (GObject    *object,
                        guint       property_id,
                        GValue     *value,
                        GParamSpec *pspec)
{
  MxAction *action = MX_ACTION (object);
  GAction *g_action = G_ACTION (object);

  switch (property_id)
    {
    case PROP_NAME:
      g_value_set_string (value, mx_action_get_name (action));
      break;

    case PROP_DISPLAY_NAME:
      g_value_set_string (value, mx_action_get_display_name (action));
      break;

    case PROP_ICON:
      g_value_set_string (value, mx_action_get_icon (action));
      break;

    case PROP_ACTIVE:
      g_value_set_boolean (value, mx_action_get_active (action));
      break;

    case PROP_PARAMETER_TYPE:
      g_value_set_boxed (value, mx_action_get_parameter_type (g_action));
      break;

    case PROP_ENABLED:
      g_value_set_boolean (value, mx_action_get_enabled (g_action));
      break;

    case PROP_STATE_TYPE:
      g_value_set_boxed (value, mx_action_get_state_type (g_action));
      break;

    case PROP_STATE:
      g_value_take_variant (value, mx_action_get_state (g_action));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}
