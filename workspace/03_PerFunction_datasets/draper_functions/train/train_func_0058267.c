gst_queue_locked_enqueue_event (GstQueue * queue, gpointer item)
{
  GstEvent *event = GST_EVENT_CAST (item);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_EOS:
      GST_CAT_LOG_OBJECT (queue_dataflow, queue, "got EOS from upstream");


      if (queue->flush_on_eos)
        gst_queue_locked_flush (queue, FALSE);
      else
        GST_QUEUE_CLEAR_LEVEL (queue->min_threshold);

      queue->eos = TRUE;
      break;
    case GST_EVENT_SEGMENT:
      apply_segment (queue, event, &queue->sink_segment, TRUE);

      if (gst_queue_array_is_empty (queue->queue)) {
        GST_CAT_LOG_OBJECT (queue_dataflow, queue, "Apply segment on srcpad");
        apply_segment (queue, event, &queue->src_segment, FALSE);
        queue->newseg_applied_to_src = TRUE;
      }


      queue->unexpected = FALSE;
      break;
    default:
      break;
  }

  if (item) {
    GstQueueItem *qitem = g_slice_new (GstQueueItem);
    qitem->item = item;
    qitem->is_query = FALSE;
    gst_queue_array_push_tail (queue->queue, qitem);
  }
  GST_QUEUE_SIGNAL_ADD (queue);
}
