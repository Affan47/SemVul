gst_queue_locked_flush (GstQueue * queue, gboolean full)
{
  while (!gst_queue_array_is_empty (queue->queue)) {
    GstQueueItem *qitem = gst_queue_array_pop_head (queue->queue);


    if (!full && !qitem->is_query && GST_IS_EVENT (qitem->item)
        && GST_EVENT_IS_STICKY (qitem->item)
        && GST_EVENT_TYPE (qitem->item) != GST_EVENT_SEGMENT
        && GST_EVENT_TYPE (qitem->item) != GST_EVENT_EOS) {
      gst_pad_store_sticky_event (queue->srcpad, GST_EVENT_CAST (qitem->item));
    }
    if (!qitem->is_query)
      gst_mini_object_unref (qitem->item);
    g_slice_free (GstQueueItem, qitem);
  }
  queue->last_query = FALSE;
  g_cond_signal (&queue->query_handled);
  GST_QUEUE_CLEAR_LEVEL (queue->cur_level);
  queue->min_threshold.buffers = queue->orig_min_threshold.buffers;
  queue->min_threshold.bytes = queue->orig_min_threshold.bytes;
  queue->min_threshold.time = queue->orig_min_threshold.time;
  gst_segment_init (&queue->sink_segment, GST_FORMAT_TIME);
  gst_segment_init (&queue->src_segment, GST_FORMAT_TIME);
  queue->head_needs_discont = queue->tail_needs_discont = FALSE;

  queue->sinktime = queue->srctime = GST_CLOCK_TIME_NONE;
  queue->sink_tainted = queue->src_tainted = TRUE;


  GST_QUEUE_SIGNAL_DEL (queue);
}
