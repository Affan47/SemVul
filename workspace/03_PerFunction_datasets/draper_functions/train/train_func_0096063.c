gst_data_queue_push_force_unlocked (GstDataQueue * queue,
    GstDataQueueItem * item)
{
  GstDataQueuePrivate *priv = queue->priv;

  gst_queue_array_push_tail (priv->queue, item);

  if (item->visible)
    priv->cur_level.visible++;
  priv->cur_level.bytes += item->size;
  priv->cur_level.time += item->duration;
}
