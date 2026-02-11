gst_audio_decoder_output (GstAudioDecoder * dec, GstBuffer * buf)
{
  GstAudioDecoderPrivate *priv;
  GstFlowReturn ret = GST_FLOW_OK;
  GstBuffer *inbuf = NULL;

  priv = dec->priv;

  if (G_UNLIKELY (priv->agg < 0))
    gst_audio_decoder_setup (dec);

  if (G_LIKELY (buf)) {
    GST_LOG_OBJECT (dec, "output buffer of size %d with ts %" GST_TIME_FORMAT
        ", duration %" GST_TIME_FORMAT, GST_BUFFER_SIZE (buf),
        GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (buf)),
        GST_TIME_ARGS (GST_BUFFER_DURATION (buf)));
  }

again:
  inbuf = NULL;
  if (priv->agg && dec->priv->latency > 0) {
    gint av;
    gboolean assemble = FALSE;
    const GstClockTimeDiff tol = 10 * GST_MSECOND;
    GstClockTimeDiff diff = -100 * GST_MSECOND;

    av = gst_adapter_available (priv->adapter_out);
    if (G_UNLIKELY (!buf)) {

      assemble = TRUE;
      GST_LOG_OBJECT (dec, "forcing fragment flush");
    } else if (av && (!GST_BUFFER_TIMESTAMP_IS_VALID (buf) ||
            !GST_CLOCK_TIME_IS_VALID (priv->out_ts) ||
            ((diff = GST_CLOCK_DIFF (GST_BUFFER_TIMESTAMP (buf),
                        priv->out_ts + priv->out_dur)) > tol) || diff < -tol)) {
      assemble = TRUE;
      GST_LOG_OBJECT (dec, "buffer %d ms apart from current fragment",
          (gint) (diff / GST_MSECOND));
    } else {

      if (!av) {
        GST_LOG_OBJECT (dec, "starting new fragment");
        priv->out_ts = GST_BUFFER_TIMESTAMP (buf);
      } else {
        GST_LOG_OBJECT (dec, "adding to fragment");
      }
      gst_adapter_push (priv->adapter_out, buf);
      priv->out_dur += GST_BUFFER_DURATION (buf);
      av += GST_BUFFER_SIZE (buf);
      buf = NULL;
    }
    if (priv->out_dur > dec->priv->latency)
      assemble = TRUE;
    if (av && assemble) {
      GST_LOG_OBJECT (dec, "assembling fragment");
      inbuf = buf;
      buf = gst_adapter_take_buffer (priv->adapter_out, av);
      GST_BUFFER_TIMESTAMP (buf) = priv->out_ts;
      GST_BUFFER_DURATION (buf) = priv->out_dur;
      priv->out_ts = GST_CLOCK_TIME_NONE;
      priv->out_dur = 0;
    }
  }

  if (G_LIKELY (buf)) {
    if (dec->segment.rate > 0.0) {
      ret = gst_audio_decoder_push_forward (dec, buf);
      GST_LOG_OBJECT (dec, "buffer pushed: %s", gst_flow_get_name (ret));
    } else {
      ret = GST_FLOW_OK;
      priv->queued = g_list_prepend (priv->queued, buf);
      GST_LOG_OBJECT (dec, "buffer queued");
    }

    if (inbuf) {
      buf = inbuf;
      goto again;
    }
  }

  return ret;
}
