gst_rfb_src_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstRfbSrc *src = GST_RFB_SRC (object);
  gchar *version;

  switch (prop_id) {
    case ARG_HOST:
      g_value_set_string (value, src->host);
      break;
    case ARG_PORT:
      g_value_set_int (value, src->port);
      break;
    case ARG_VERSION:
      version = gst_rfb_property_get_version (src);
      g_value_set_string (value, version);
      g_free (version);
      break;
    case ARG_OFFSET_X:
      g_value_set_int (value, src->decoder->offset_x);
      break;
    case ARG_OFFSET_Y:
      g_value_set_int (value, src->decoder->offset_y);
      break;
    case ARG_WIDTH:
      g_value_set_int (value, src->decoder->rect_width);
      break;
    case ARG_HEIGHT:
      g_value_set_int (value, src->decoder->rect_height);
      break;
    case ARG_INCREMENTAL:
      g_value_set_boolean (value, src->incremental_update);
      break;
    case ARG_USE_COPYRECT:
      g_value_set_boolean (value, src->decoder->use_copyrect);
      break;
    case ARG_SHARED:
      g_value_set_boolean (value, src->decoder->shared_flag);
      break;
    case ARG_VIEWONLY:
      g_value_set_boolean (value, src->view_only);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
