gst_queue2_locked_dequeue (GstQueue2 * queue, GstQueue2ItemType * item_type)
{
  GstMiniObject *item;

  if (!QUEUE_IS_USING_QUEUE (queue)) {
    item = gst_queue2_read_item_from_file (queue);
  } else {
    GstQueue2Item *qitem = g_queue_pop_head (&queue->queue);

    if (qitem == NULL)
      goto no_item;

    item = qitem->item;
    g_slice_free (GstQueue2Item, qitem);
  }

  if (item == NULL)
    goto no_item;

  if (GST_IS_BUFFER (item)) {
    GstBuffer *buffer;
    guint size;

    buffer = GST_BUFFER_CAST (item);
    size = gst_buffer_get_size (buffer);
    *item_type = GST_QUEUE2_ITEM_TYPE_BUFFER;

    GST_CAT_LOG_OBJECT (queue_dataflow, queue,
        "retrieved buffer %p from queue", buffer);

    if (QUEUE_IS_USING_QUEUE (queue)) {
      queue->cur_level.buffers--;
      queue->cur_level.bytes -= size;
    }
    queue->bytes_out += size;

    apply_buffer (queue, buffer, &queue->src_segment, FALSE);

    update_out_rates (queue);

    if (queue->use_buffering)
      update_buffering (queue);

  } else if (GST_IS_EVENT (item)) {
    GstEvent *event = GST_EVENT_CAST (item);

    *item_type = GST_QUEUE2_ITEM_TYPE_EVENT;

    GST_CAT_LOG_OBJECT (queue_dataflow, queue,
        "retrieved event %p from queue", event);

    switch (GST_EVENT_TYPE (event)) {
      case GST_EVENT_EOS:

        GST_QUEUE2_CLEAR_LEVEL (queue->cur_level);
        break;
      case GST_EVENT_SEGMENT:
        apply_segment (queue, event, &queue->src_segment, FALSE);
        break;
      default:
        break;
    }
  } else if (GST_IS_BUFFER_LIST (item)) {
    GstBufferList *buffer_list;
    guint size = 0;

    buffer_list = GST_BUFFER_LIST_CAST (item);
    gst_buffer_list_foreach (buffer_list, buffer_list_calc_size, &size);
    *item_type = GST_QUEUE2_ITEM_TYPE_BUFFER_LIST;

    GST_CAT_LOG_OBJECT (queue_dataflow, queue,
        "retrieved buffer list %p from queue", buffer_list);

    if (QUEUE_IS_USING_QUEUE (queue)) {
      queue->cur_level.buffers--;
      queue->cur_level.bytes -= size;
    }
    queue->bytes_out += size;

    apply_buffer_list (queue, buffer_list, &queue->src_segment, FALSE);

    update_out_rates (queue);

    if (queue->use_buffering)
      update_buffering (queue);
  } else if (GST_IS_QUERY (item)) {
    GST_CAT_LOG_OBJECT (queue_dataflow, queue,
        "retrieved query %p from queue", item);
    *item_type = GST_QUEUE2_ITEM_TYPE_QUERY;
  } else {
    g_warning
        ("Unexpected item %p dequeued from queue %s (refcounting problem?)",
        item, GST_OBJECT_NAME (queue));
    item = NULL;
    *item_type = GST_QUEUE2_ITEM_TYPE_UNKNOWN;
  }
  GST_QUEUE2_SIGNAL_DEL (queue);

  return item;


no_item:
  {
    GST_CAT_LOG_OBJECT (queue_dataflow, queue, "the queue is empty");
    return NULL;
  }
}
