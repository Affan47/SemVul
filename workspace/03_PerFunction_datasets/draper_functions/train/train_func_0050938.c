gst_alaw_dec_chain (GstPad * pad, GstObject * parent, GstBuffer * buffer)
{
  GstALawDec *alawdec;
  GstMapInfo inmap, outmap;
  gint16 *linear_data;
  guint8 *alaw_data;
  gsize alaw_size, linear_size;
  GstBuffer *outbuf;
  gint i;
  GstFlowReturn ret;

  alawdec = GST_ALAW_DEC (parent);

  if (G_UNLIKELY (!GST_AUDIO_INFO_IS_VALID (&alawdec->info)))
    goto not_negotiated;

  GST_LOG_OBJECT (alawdec, "buffer with ts=%" GST_TIME_FORMAT,
      GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (buffer)));

  gst_buffer_map (buffer, &inmap, GST_MAP_READ);
  alaw_data = inmap.data;
  alaw_size = inmap.size;

  linear_size = alaw_size * 2;

  outbuf = gst_buffer_new_allocate (NULL, linear_size, NULL);

  gst_buffer_map (outbuf, &outmap, GST_MAP_WRITE);
  linear_data = (gint16 *) outmap.data;


  if (GST_BUFFER_FLAG_IS_SET (buffer, GST_BUFFER_FLAG_DISCONT))
    GST_BUFFER_FLAG_SET (outbuf, GST_BUFFER_FLAG_DISCONT);

  GST_BUFFER_TIMESTAMP (outbuf) = GST_BUFFER_TIMESTAMP (buffer);
  if (GST_BUFFER_DURATION_IS_VALID (buffer)) {
    GST_BUFFER_DURATION (outbuf) = GST_BUFFER_DURATION (buffer);
  } else {
    GST_BUFFER_DURATION (outbuf) = gst_util_uint64_scale_int (GST_SECOND,
        linear_size, GST_AUDIO_INFO_RATE (&alawdec->info) *
        GST_AUDIO_INFO_BPF (&alawdec->info));
  }

  for (i = 0; i < alaw_size; i++) {
    linear_data[i] = alaw_to_s16 (alaw_data[i]);
  }

  gst_buffer_unmap (outbuf, &outmap);
  gst_buffer_unmap (buffer, &inmap);
  gst_buffer_unref (buffer);

  ret = gst_pad_push (alawdec->srcpad, outbuf);

  return ret;

not_negotiated:
  {
    gst_buffer_unref (buffer);
    GST_WARNING_OBJECT (alawdec, "no input format set: not-negotiated");
    return GST_FLOW_NOT_NEGOTIATED;
  }
}
