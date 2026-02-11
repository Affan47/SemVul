gst_vp8_enc_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstVP8Enc *gst_vp8_enc;

  g_return_if_fail (GST_IS_VP8_ENC (object));
  gst_vp8_enc = GST_VP8_ENC (object);

  GST_DEBUG_OBJECT (object, "gst_vp8_enc_set_property");
  switch (prop_id) {
    case PROP_BITRATE:
      gst_vp8_enc->bitrate = g_value_get_int (value);
      break;
    case PROP_MODE:
      gst_vp8_enc->mode = g_value_get_enum (value);
      break;
    case PROP_MINSECTION_PCT:
      gst_vp8_enc->minsection_pct = g_value_get_uint (value);
      break;
    case PROP_MAXSECTION_PCT:
      gst_vp8_enc->maxsection_pct = g_value_get_uint (value);
      break;
    case PROP_MIN_QUANTIZER:
      gst_vp8_enc->min_quantizer = g_value_get_int (value);
      break;
    case PROP_MAX_QUANTIZER:
      gst_vp8_enc->max_quantizer = g_value_get_int (value);
      break;
    case PROP_QUALITY:
      gst_vp8_enc->quality = g_value_get_double (value);
      break;
    case PROP_ERROR_RESILIENT:
      gst_vp8_enc->error_resilient = g_value_get_boolean (value);
      break;
    case PROP_MAX_LATENCY:
      gst_vp8_enc->max_latency = g_value_get_int (value);
      break;
    case PROP_MAX_KEYFRAME_DISTANCE:
      gst_vp8_enc->max_keyframe_distance = g_value_get_int (value);
      break;
    case PROP_SPEED:
      gst_vp8_enc->speed = g_value_get_int (value);
      break;
    case PROP_THREADS:
      gst_vp8_enc->threads = g_value_get_int (value);
      break;
    case PROP_MULTIPASS_MODE:
      gst_vp8_enc->multipass_mode = g_value_get_enum (value);
      break;
    case PROP_MULTIPASS_CACHE_FILE:
      if (gst_vp8_enc->multipass_cache_file)
        g_free (gst_vp8_enc->multipass_cache_file);
      gst_vp8_enc->multipass_cache_file = g_value_dup_string (value);
      break;
    case PROP_AUTO_ALT_REF_FRAMES:
      gst_vp8_enc->auto_alt_ref_frames = g_value_get_boolean (value);
      break;
    case PROP_LAG_IN_FRAMES:
      gst_vp8_enc->lag_in_frames = g_value_get_uint (value);
      break;
    case PROP_SHARPNESS:
      gst_vp8_enc->sharpness = g_value_get_int (value);
      break;
    case PROP_NOISE_SENSITIVITY:
      gst_vp8_enc->noise_sensitivity = g_value_get_int (value);
      break;
    case PROP_TUNE:
#ifdef HAVE_VP8ENC_TUNING
      gst_vp8_enc->tuning = g_value_get_enum (value);
#else
      GST_WARNING_OBJECT (gst_vp8_enc,
          "The tuning property is unsupported by this libvpx");
#endif
      break;
    case PROP_STATIC_THRESHOLD:
      gst_vp8_enc->static_threshold = g_value_get_int (value);
      break;
    case PROP_DROP_FRAME:
      gst_vp8_enc->drop_frame = g_value_get_int (value);
      break;
    case PROP_RESIZE_ALLOWED:
      gst_vp8_enc->resize_allowed = g_value_get_boolean (value);
      break;
    case PROP_TOKEN_PARTS:
      gst_vp8_enc->partitions = g_value_get_int (value);
      break;
    default:
      break;
  }
}
