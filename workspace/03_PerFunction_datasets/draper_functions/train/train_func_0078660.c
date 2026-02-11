gst_interpolation_control_source_set_interpolation_mode (
    GstInterpolationControlSource * self, GstInterpolateMode mode)

{
  gboolean ret = TRUE;
  GstControlSource *csource = GST_CONTROL_SOURCE (self);

  if (mode >= priv_gst_num_interpolation_methods
      || priv_gst_interpolation_methods[mode] == NULL) {
    GST_WARNING ("interpolation mode %d invalid or not implemented yet", mode);
    return FALSE;
  }

  if (mode == GST_INTERPOLATE_QUADRATIC) {
    GST_WARNING ("Quadratic interpolation mode is deprecated, using cubic"
        "interpolation mode");
  }

  if (mode == GST_INTERPOLATE_USER) {
    GST_WARNING ("User interpolation mode is not implemented yet");
    return FALSE;
  }

  g_mutex_lock (self->lock);
  switch (self->priv->base) {
    case G_TYPE_INT:
      csource->get_value = priv_gst_interpolation_methods[mode]->get_int;
      csource->get_value_array =
          priv_gst_interpolation_methods[mode]->get_int_value_array;
      break;
    case G_TYPE_UINT:{
      csource->get_value = priv_gst_interpolation_methods[mode]->get_uint;
      csource->get_value_array =
          priv_gst_interpolation_methods[mode]->get_uint_value_array;
      break;
    }
    case G_TYPE_LONG:{
      csource->get_value = priv_gst_interpolation_methods[mode]->get_long;
      csource->get_value_array =
          priv_gst_interpolation_methods[mode]->get_long_value_array;
      break;
    }
    case G_TYPE_ULONG:{
      csource->get_value = priv_gst_interpolation_methods[mode]->get_ulong;
      csource->get_value_array =
          priv_gst_interpolation_methods[mode]->get_ulong_value_array;
      break;
    }
    case G_TYPE_INT64:{
      csource->get_value = priv_gst_interpolation_methods[mode]->get_int64;
      csource->get_value_array =
          priv_gst_interpolation_methods[mode]->get_int64_value_array;
      break;
    }
    case G_TYPE_UINT64:{
      csource->get_value = priv_gst_interpolation_methods[mode]->get_uint64;
      csource->get_value_array =
          priv_gst_interpolation_methods[mode]->get_uint64_value_array;
      break;
    }
    case G_TYPE_FLOAT:{
      csource->get_value = priv_gst_interpolation_methods[mode]->get_float;
      csource->get_value_array =
          priv_gst_interpolation_methods[mode]->get_float_value_array;
      break;
    }
    case G_TYPE_DOUBLE:{
      csource->get_value = priv_gst_interpolation_methods[mode]->get_double;
      csource->get_value_array =
          priv_gst_interpolation_methods[mode]->get_double_value_array;
      break;
    }
    case G_TYPE_BOOLEAN:{
      csource->get_value = priv_gst_interpolation_methods[mode]->get_boolean;
      csource->get_value_array =
          priv_gst_interpolation_methods[mode]->get_boolean_value_array;
      break;
    }
    case G_TYPE_ENUM:{
      csource->get_value = priv_gst_interpolation_methods[mode]->get_enum;
      csource->get_value_array =
          priv_gst_interpolation_methods[mode]->get_enum_value_array;
      break;
    }
    case G_TYPE_STRING:{
      csource->get_value = priv_gst_interpolation_methods[mode]->get_string;
      csource->get_value_array =
          priv_gst_interpolation_methods[mode]->get_string_value_array;
      break;
    }
    default:
      ret = FALSE;
      break;
  }


  if (!ret || !csource->get_value || !csource->get_value_array) {
    gst_interpolation_control_source_reset (self);
    ret = FALSE;
  }

  self->priv->valid_cache = FALSE;
  self->priv->interpolation_mode = mode;

  g_mutex_unlock (self->lock);

  return ret;
}
