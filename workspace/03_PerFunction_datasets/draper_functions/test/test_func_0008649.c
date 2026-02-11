gst_funnel_sink_chain (GstPad * pad, GstObject * parent, GstBuffer * buffer)
{
  GstFlowReturn res;
  GstFunnel *funnel = GST_FUNNEL (parent);

  GST_DEBUG_OBJECT (funnel, "received buffer %p", buffer);

  GST_PAD_STREAM_LOCK (funnel->srcpad);

  if (funnel->last_sinkpad != pad) {
    gst_object_replace ((GstObject **) & funnel->last_sinkpad,
        GST_OBJECT (pad));

    gst_pad_sticky_events_foreach (pad, forward_events, funnel->srcpad);
  }

  res = gst_pad_push (funnel->srcpad, buffer);

  GST_PAD_STREAM_UNLOCK (funnel->srcpad);

  GST_LOG_OBJECT (funnel, "handled buffer %s", gst_flow_get_name (res));

  return res;
}
