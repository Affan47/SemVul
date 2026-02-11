gst_cdda_base_src_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstCddaBaseSrcClass *klass = GST_CDDA_BASE_SRC_GET_CLASS (object);
  GstCddaBaseSrc *src = GST_CDDA_BASE_SRC (object);

  GST_OBJECT_LOCK (src);

  switch (prop_id) {
    case ARG_MODE:
      g_value_set_enum (value, src->mode);
      break;
    case ARG_DEVICE:{
      if (src->device == NULL && klass->get_default_device != NULL) {
        gchar *d = klass->get_default_device (src);

        if (d != NULL) {
          g_value_set_string (value, DEFAULT_DEVICE);
          g_free (d);
          break;
        }
      }
      if (src->device == NULL)
        g_value_set_string (value, DEFAULT_DEVICE);
      else
        g_value_set_string (value, src->device);
      break;
    }
    case ARG_TRACK:{
      if (src->num_tracks <= 0 && src->uri_track > 0) {
        g_value_set_uint (value, src->uri_track);
      } else {
        g_value_set_uint (value, src->cur_track + 1);
      }
      break;
    }
    case ARG_TOC_OFFSET:
      g_value_set_int (value, src->toc_offset);
      break;
    case ARG_TOC_BIAS:
      g_value_set_boolean (value, src->toc_bias);
      break;
    default:{
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
  }

  GST_OBJECT_UNLOCK (src);
}
