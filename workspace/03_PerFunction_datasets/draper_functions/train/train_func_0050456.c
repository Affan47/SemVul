gst_single_queue_push_one (GstMultiQueue * mq, GstSingleQueue * sq,
    GstMiniObject * object)
{
  GstFlowReturn result = GST_FLOW_OK;

  if (GST_IS_BUFFER (object)) {
    GstBuffer *buffer;
    GstClockTime timestamp, duration;
    GstCaps *caps;

    buffer = GST_BUFFER_CAST (object);
    timestamp = GST_BUFFER_TIMESTAMP (buffer);
    duration = GST_BUFFER_DURATION (buffer);
    caps = GST_BUFFER_CAPS (buffer);

    apply_buffer (mq, sq, timestamp, duration, &sq->src_segment);


    gst_data_queue_limits_changed (sq->queue);

    GST_DEBUG_OBJECT (mq,
        "SingleQueue %d : Pushing buffer %p with ts %" GST_TIME_FORMAT,
        sq->id, buffer, GST_TIME_ARGS (timestamp));


    if (caps && caps != GST_PAD_CAPS (sq->srcpad))
      gst_pad_set_caps (sq->srcpad, caps);

    result = gst_pad_push (sq->srcpad, buffer);
  } else if (GST_IS_EVENT (object)) {
    GstEvent *event;

    event = GST_EVENT_CAST (object);

    switch (GST_EVENT_TYPE (event)) {
      case GST_EVENT_EOS:
        result = GST_FLOW_UNEXPECTED;
        break;
      case GST_EVENT_NEWSEGMENT:
        apply_segment (mq, sq, event, &sq->src_segment);

        gst_data_queue_limits_changed (sq->queue);
        break;
      default:
        break;
    }

    GST_DEBUG_OBJECT (mq,
        "SingleQueue %d : Pushing event %p of type %s",
        sq->id, event, GST_EVENT_TYPE_NAME (event));

    gst_pad_push_event (sq->srcpad, event);
  } else {
    g_warning ("Unexpected object in singlequeue %d (refcounting problem?)",
        sq->id);
  }
  return result;


}
