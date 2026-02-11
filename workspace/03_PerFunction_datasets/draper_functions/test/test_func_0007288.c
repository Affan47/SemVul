gst_queue2_chain (GstPad * pad, GstBuffer * buffer)
{
  GstQueue2 *queue;

  queue = GST_QUEUE2 (GST_OBJECT_PARENT (pad));

  GST_CAT_LOG_OBJECT (queue_dataflow, queue,
      "received buffer %p of size %d, time %" GST_TIME_FORMAT ", duration %"
      GST_TIME_FORMAT, buffer, GST_BUFFER_SIZE (buffer),
      GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (buffer)),
      GST_TIME_ARGS (GST_BUFFER_DURATION (buffer)));

  return gst_queue2_chain_buffer_or_buffer_list (queue,
      GST_MINI_OBJECT_CAST (buffer), GST_QUEUE2_ITEM_TYPE_BUFFER);
}
