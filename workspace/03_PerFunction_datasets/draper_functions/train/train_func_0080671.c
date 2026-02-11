get_seek_threshold (GstQueue2 * queue)
{
  guint64 threshold;


  threshold = 1024 * 512;

  if (QUEUE_IS_USING_RING_BUFFER (queue)) {
    threshold = MIN (threshold,
        QUEUE_MAX_BYTES (queue) - queue->cur_level.bytes);
  }
  return threshold;
}
