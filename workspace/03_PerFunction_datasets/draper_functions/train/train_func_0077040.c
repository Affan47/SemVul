gst_audio_encoder_sink_query (GstPad * pad, GstObject * parent,
    GstQuery * query)
{
  gboolean res = FALSE;
  GstAudioEncoder *enc;

  enc = GST_AUDIO_ENCODER (parent);

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_FORMATS:
    {
      gst_query_set_formats (query, 3,
          GST_FORMAT_TIME, GST_FORMAT_BYTES, GST_FORMAT_DEFAULT);
      res = TRUE;
      break;
    }
    case GST_QUERY_CONVERT:
    {
      GstFormat src_fmt, dest_fmt;
      gint64 src_val, dest_val;

      gst_query_parse_convert (query, &src_fmt, &src_val, &dest_fmt, &dest_val);
      if (!(res = gst_audio_info_convert (&enc->priv->ctx.info,
                  src_fmt, src_val, dest_fmt, &dest_val)))
        goto error;
      gst_query_set_convert (query, src_fmt, src_val, dest_fmt, dest_val);
      res = TRUE;
      break;
    }
    case GST_QUERY_CAPS:
    {
      GstCaps *filter, *caps;
      GstAudioEncoderClass *klass;

      gst_query_parse_caps (query, &filter);

      klass = GST_AUDIO_ENCODER_GET_CLASS (enc);
      if (klass->getcaps) {
        caps = klass->getcaps (enc, filter);
        gst_query_set_caps_result (query, caps);
        gst_caps_unref (caps);
        res = TRUE;
      }
      break;
    }
    case GST_QUERY_ALLOCATION:
    {
      GstAudioEncoderClass *klass = GST_AUDIO_ENCODER_GET_CLASS (enc);

      if (klass->propose_allocation)
        res = klass->propose_allocation (enc, query);
      break;
    }
    default:
      res = gst_pad_query_default (pad, parent, query);
      break;
  }

error:
  return res;
}
