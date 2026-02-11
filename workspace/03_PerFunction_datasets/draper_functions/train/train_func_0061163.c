gst_audio_decoder_sink_query (GstPad * pad, GstQuery * query)
{
  gboolean res = TRUE;
  GstAudioDecoder *dec;

  dec = GST_AUDIO_DECODER (gst_pad_get_parent (pad));

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_FORMATS:
    {
      gst_query_set_formats (query, 2, GST_FORMAT_TIME, GST_FORMAT_BYTES);
      res = TRUE;
      break;
    }
    case GST_QUERY_CONVERT:
    {
      GstFormat src_fmt, dest_fmt;
      gint64 src_val, dest_val;

      gst_query_parse_convert (query, &src_fmt, &src_val, &dest_fmt, &dest_val);
      if (!(res = gst_audio_encoded_audio_convert (&dec->priv->ctx.info,
                  dec->priv->bytes_in, dec->priv->samples_out,
                  src_fmt, src_val, &dest_fmt, &dest_val)))
        goto error;
      gst_query_set_convert (query, src_fmt, src_val, dest_fmt, dest_val);
      break;
    }
    default:
      res = gst_pad_query_default (pad, query);
      break;
  }

error:
  gst_object_unref (dec);
  return res;
}
