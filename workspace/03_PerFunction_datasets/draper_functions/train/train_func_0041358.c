gst_alaw_dec_chain (GstPad * pad, GstBuffer * buffer)
{
  GstALawDec *alawdec;
  gint16 *linear_data;
  guint8 *alaw_data;
  guint alaw_size;
  GstBuffer *outbuf;
  gint i;
  GstFlowReturn ret;

  alawdec = GST_ALAW_DEC (GST_PAD_PARENT (pad));

  if (G_UNLIKELY (alawdec->rate == 0))
    goto not_negotiated;

  GST_LOG_OBJECT (alawdec, "buffer with ts=%" GST_TIME_FORMAT,
      GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (buffer)));

  alaw_data = GST_BUFFER_DATA (buffer);
  alaw_size = GST_BUFFER_SIZE (buffer);

  ret =
      gst_pad_alloc_buffer_and_set_caps (alawdec->srcpad,
      GST_BUFFER_OFFSET_NONE, alaw_size * 2, GST_PAD_CAPS (alawdec->srcpad),
      &outbuf);
  if (ret != GST_FLOW_OK)
    goto alloc_failed;

  linear_data = (gint16 *) GST_BUFFER_DATA (outbuf);


  if (GST_BUFFER_FLAG_IS_SET (buffer, GST_BUFFER_FLAG_DISCONT))
    GST_BUFFER_FLAG_SET (outbuf, GST_BUFFER_FLAG_DISCONT);

  GST_BUFFER_TIMESTAMP (outbuf) = GST_BUFFER_TIMESTAMP (buffer);
  GST_BUFFER_DURATION (outbuf) = GST_BUFFER_DURATION (buffer);
  gst_buffer_set_caps (outbuf, GST_PAD_CAPS (alawdec->srcpad));

  for (i = 0; i < alaw_size; i++) {
    linear_data[i] = alaw_to_s16 (alaw_data[i]);
  }
  gst_buffer_unref (buffer);

  ret = gst_pad_push (alawdec->srcpad, outbuf);

  return ret;

not_negotiated:
  {
    gst_buffer_unref (buffer);
    GST_WARNING_OBJECT (alawdec, "no input format set: not-negotiated");
    return GST_FLOW_NOT_NEGOTIATED;
  }
alloc_failed:
  {
    gst_buffer_unref (buffer);
    GST_DEBUG_OBJECT (alawdec, "pad alloc failed, flow: %s",
        gst_flow_get_name (ret));
    return ret;
  }
}
