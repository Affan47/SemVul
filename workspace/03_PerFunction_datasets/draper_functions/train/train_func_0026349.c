clutter_drag_action_get_property (GObject    *gobject,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspec)
{
  ClutterDragActionPrivate *priv = CLUTTER_DRAG_ACTION (gobject)->priv;

  switch (prop_id)
    {
    case PROP_X_DRAG_THRESHOLD:
      {
        gint threshold;

        get_drag_threshold (CLUTTER_DRAG_ACTION (gobject), &threshold, NULL);
        g_value_set_int (value, threshold);
      }
      break;

    case PROP_Y_DRAG_THRESHOLD:
      {
        gint threshold;

        get_drag_threshold (CLUTTER_DRAG_ACTION (gobject), NULL, &threshold);
        g_value_set_int (value, threshold);
      }
      break;

    case PROP_DRAG_HANDLE:
      g_value_set_object (value, priv->drag_handle);
      break;

    case PROP_DRAG_AXIS:
      g_value_set_enum (value, priv->drag_axis);
      break;

    case PROP_DRAG_AREA:
      g_value_set_boxed (value, &priv->drag_area);
      break;

    case PROP_DRAG_AREA_SET:
      g_value_set_boolean (value, priv->drag_area_set);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (gobject, prop_id, pspec);
    }
}
