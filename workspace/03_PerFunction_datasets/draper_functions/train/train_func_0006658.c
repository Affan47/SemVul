gst_selector_pad_chain (GstPad * pad, GstBuffer * buf)
{
  RsnStreamSelector *sel;
  GstFlowReturn res;
  GstPad *active_sinkpad;
  RsnSelectorPad *selpad;
  GstClockTime timestamp;
  GstSegment *seg;
  gboolean discont;

  sel = RSN_STREAM_SELECTOR (gst_pad_get_parent (pad));
  selpad = GST_SELECTOR_PAD_CAST (pad);
  seg = &selpad->segment;

  active_sinkpad = rsn_stream_selector_get_active (sel, pad);

  timestamp = GST_BUFFER_TIMESTAMP (buf);
  if (GST_CLOCK_TIME_IS_VALID (timestamp)) {
    GST_DEBUG_OBJECT (sel, "received timestamp %" GST_TIME_FORMAT,
        GST_TIME_ARGS (timestamp));
    gst_segment_set_last_stop (seg, seg->format, timestamp);
  }


  if (pad != active_sinkpad)
    goto ignore;


  GST_OBJECT_LOCK (sel);
  discont = sel->mark_discont;
  sel->mark_discont = FALSE;
  GST_OBJECT_UNLOCK (sel);

  if (discont) {
    GST_DEBUG_OBJECT (sel, "Marking buffer discont due to pad switch");
    buf = gst_buffer_make_metadata_writable (buf);
    GST_BUFFER_FLAG_SET (buf, GST_BUFFER_FLAG_DISCONT);
  }


  GST_LOG_OBJECT (sel, "Forwarding buffer %p from pad %s:%s", buf,
      GST_DEBUG_PAD_NAME (pad));
  res = gst_pad_push (sel->srcpad, buf);
done:
  gst_object_unref (sel);
  return res;

ignore:
  {
    GST_DEBUG_OBJECT (sel, "Ignoring buffer %p from pad %s:%s",
        buf, GST_DEBUG_PAD_NAME (pad));
    gst_buffer_unref (buf);
    res = GST_FLOW_NOT_LINKED;
    goto done;
  }
}
