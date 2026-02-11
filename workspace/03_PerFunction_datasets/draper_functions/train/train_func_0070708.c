clutter_table_layout_set_property (GObject      *gobject,
                                   guint         prop_id,
                                   const GValue *value,
                                   GParamSpec   *pspec)
{
  ClutterTableLayout *self = CLUTTER_TABLE_LAYOUT (gobject);

  switch (prop_id)
    {
    case PROP_COLUMN_SPACING:
      clutter_table_layout_set_column_spacing (self, g_value_get_uint (value));
      break;

    case PROP_ROW_SPACING:
      clutter_table_layout_set_row_spacing (self, g_value_get_uint (value));
      break;

    case PROP_USE_ANIMATIONS:
      clutter_table_layout_set_use_animations (self, g_value_get_boolean (value));
      break;

    case PROP_EASING_MODE:
      clutter_table_layout_set_easing_mode (self, g_value_get_ulong (value));
      break;

    case PROP_EASING_DURATION:
      clutter_table_layout_set_easing_duration (self, g_value_get_uint (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (gobject, prop_id, pspec);
      break;
    }
}
