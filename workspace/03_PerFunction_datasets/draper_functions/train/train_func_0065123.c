gst_queue2_locked_flush (GstQueue2 * queue, gboolean full)
{
  if (!QUEUE_IS_USING_QUEUE (queue)) {
    if (QUEUE_IS_USING_TEMP_FILE (queue))
      gst_queue2_flush_temp_file (queue);
    init_ranges (queue);
  } else {
    while (!g_queue_is_empty (&queue->queue)) {
      GstQueue2Item *qitem = g_queue_pop_head (&queue->queue);

      if (!full && qitem->type == GST_QUEUE2_ITEM_TYPE_EVENT
          && GST_EVENT_IS_STICKY (qitem->item)
          && GST_EVENT_TYPE (qitem->item) != GST_EVENT_SEGMENT
          && GST_EVENT_TYPE (qitem->item) != GST_EVENT_EOS) {
        gst_pad_store_sticky_event (queue->srcpad,
            GST_EVENT_CAST (qitem->item));
      }


      if (qitem->type != GST_QUEUE2_ITEM_TYPE_QUERY)
        gst_mini_object_unref (qitem->item);
      g_slice_free (GstQueue2Item, qitem);
    }
  }
  queue->last_query = FALSE;
  g_cond_signal (&queue->query_handled);
  GST_QUEUE2_CLEAR_LEVEL (queue->cur_level);
  gst_segment_init (&queue->sink_segment, GST_FORMAT_TIME);
  gst_segment_init (&queue->src_segment, GST_FORMAT_TIME);
  queue->sinktime = queue->srctime = GST_CLOCK_TIME_NONE;
  queue->sink_tainted = queue->src_tainted = TRUE;
  if (queue->starting_segment != NULL)
    gst_event_unref (queue->starting_segment);
  queue->starting_segment = NULL;
  queue->segment_event_received = FALSE;
  gst_event_replace (&queue->stream_start_event, NULL);


  GST_QUEUE2_SIGNAL_DEL (queue);
}
