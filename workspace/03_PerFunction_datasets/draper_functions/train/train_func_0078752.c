gst_base_sink_loop (GstPad * pad)
{
  GstObject *parent;
  GstBaseSink *basesink;
  GstBuffer *buf = NULL;
  GstFlowReturn result;
  guint blocksize;
  guint64 offset;

  parent = GST_OBJECT_PARENT (pad);
  basesink = GST_BASE_SINK (parent);

  g_assert (basesink->pad_mode == GST_PAD_MODE_PULL);

  if ((blocksize = basesink->priv->blocksize) == 0)
    blocksize = -1;

  offset = basesink->segment.position;

  GST_DEBUG_OBJECT (basesink, "pulling %" G_GUINT64_FORMAT ", %u",
      offset, blocksize);

  result = gst_pad_pull_range (pad, offset, blocksize, &buf);
  if (G_UNLIKELY (result != GST_FLOW_OK))
    goto paused;

  if (G_UNLIKELY (buf == NULL))
    goto no_buffer;

  offset += gst_buffer_get_size (buf);

  basesink->segment.position = offset;

  GST_BASE_SINK_PREROLL_LOCK (basesink);
  result = gst_base_sink_chain_unlocked (basesink, pad, buf, FALSE);
  GST_BASE_SINK_PREROLL_UNLOCK (basesink);
  if (G_UNLIKELY (result != GST_FLOW_OK))
    goto paused;

  return;


paused:
  {
    GST_LOG_OBJECT (basesink, "pausing task, reason %s",
        gst_flow_get_name (result));
    gst_pad_pause_task (pad);
    if (result == GST_FLOW_EOS) {

      if (basesink->segment.flags & GST_SEGMENT_FLAG_SEGMENT) {
        gst_element_post_message (GST_ELEMENT_CAST (basesink),
            gst_message_new_segment_done (GST_OBJECT_CAST (basesink),
                basesink->segment.format, basesink->segment.position));
        gst_base_sink_event (pad, parent,
            gst_event_new_segment_done (basesink->segment.format,
                basesink->segment.position));
      } else {
        gst_base_sink_event (pad, parent, gst_event_new_eos ());
      }
    } else if (result == GST_FLOW_NOT_LINKED || result <= GST_FLOW_EOS) {


      GST_ELEMENT_ERROR (basesink, STREAM, FAILED,
          (_("Internal data stream error.")),
          ("stream stopped, reason %s", gst_flow_get_name (result)));
      gst_base_sink_event (pad, parent, gst_event_new_eos ());
    }
    return;
  }
no_buffer:
  {
    GST_LOG_OBJECT (basesink, "no buffer, pausing");
    GST_ELEMENT_ERROR (basesink, STREAM, FAILED,
        (_("Internal data flow error.")), ("element returned NULL buffer"));
    result = GST_FLOW_ERROR;
    goto paused;
  }
}
