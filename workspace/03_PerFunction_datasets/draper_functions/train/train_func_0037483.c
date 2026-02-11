gst_data_queue_flush (GstDataQueue * queue)
{
  GST_DEBUG ("queue:%p", queue);
  GST_DATA_QUEUE_MUTEX_LOCK (queue);
  gst_data_queue_locked_flush (queue);
  GST_DATA_QUEUE_MUTEX_UNLOCK (queue);
}
