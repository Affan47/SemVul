gst_rsvg_overlay_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstRsvgOverlay *overlay = GST_RSVG_OVERLAY (object);

  GST_RSVG_LOCK (overlay);

  switch (prop_id) {
    case PROP_DATA:
    {
      gst_rsvg_overlay_set_svg_data (overlay, g_value_get_string (value),
          FALSE);
      break;
    }
    case PROP_LOCATION:
    {
      gst_rsvg_overlay_set_svg_data (overlay, g_value_get_string (value), TRUE);
      break;
    }
    case PROP_FIT_TO_FRAME:
    {
      if (g_value_get_boolean (value)) {
        overlay->x_offset = 0;
        overlay->y_offset = 0;
        overlay->x_relative = 0.0;
        overlay->y_relative = 0.0;
        overlay->width = 0;
        overlay->height = 0;
        overlay->width_relative = 1.0;
        overlay->height_relative = 1.0;
      } else {
        overlay->width_relative = 0;
        overlay->height_relative = 0;
      }
      break;
    }
    case PROP_X:
    {
      overlay->x_offset = g_value_get_int (value);
      break;
    }
    case PROP_Y:
    {
      overlay->y_offset = g_value_get_int (value);
      break;
    }
    case PROP_X_RELATIVE:
    {
      overlay->x_relative = g_value_get_float (value);
      break;
    }
    case PROP_Y_RELATIVE:
    {
      overlay->y_relative = g_value_get_float (value);
      break;
    }

    case PROP_WIDTH:
    {
      overlay->width = g_value_get_int (value);
      break;
    }
    case PROP_HEIGHT:
    {
      overlay->height = g_value_get_int (value);
      break;
    }
    case PROP_WIDTH_RELATIVE:
    {
      overlay->width_relative = g_value_get_float (value);
      break;
    }
    case PROP_HEIGHT_RELATIVE:
    {
      overlay->height_relative = g_value_get_float (value);
      break;
    }

    default:
    {
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
  }

  GST_RSVG_UNLOCK (overlay);
}
