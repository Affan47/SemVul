gst_rnd_buffer_size_sink_event (GstPad * pad, GstObject * parent,
    GstEvent * event)
{
  GstRndBufferSize *rnd = GST_RND_BUFFER_SIZE (parent);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_EOS:
      gst_rnd_buffer_size_drain_adapter (rnd, TRUE);
      break;
    case GST_EVENT_FLUSH_STOP:
      if (rnd->adapter != NULL)
        gst_adapter_clear (rnd->adapter);
      break;
    default:
      break;
  }

  return gst_pad_event_default (pad, parent, event);
}
