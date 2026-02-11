update_in_rates (GstQueue2 * queue)
{
  gdouble elapsed, period;
  gdouble byte_in_rate;

  if (!queue->in_timer_started) {
    queue->in_timer_started = TRUE;
    g_timer_start (queue->in_timer);
    return;
  }

  elapsed = g_timer_elapsed (queue->in_timer, NULL);


  if (queue->last_in_elapsed + RATE_INTERVAL < elapsed) {
    period = elapsed - queue->last_in_elapsed;

    GST_DEBUG_OBJECT (queue,
        "rates: period %f, in %" G_GUINT64_FORMAT ", global period %f",
        period, queue->bytes_in, queue->byte_in_period);

    byte_in_rate = queue->bytes_in / period;

    if (queue->byte_in_rate == 0.0)
      queue->byte_in_rate = byte_in_rate;
    else
      queue->byte_in_rate = AVG_IN (queue->byte_in_rate, byte_in_rate,
          (double) queue->byte_in_period, period);


    if (queue->byte_in_period < 16 * RATE_INTERVAL)
      queue->byte_in_period += period;


    queue->last_in_elapsed = elapsed;
    queue->bytes_in = 0;
  }

  if (queue->byte_in_rate > 0.0) {
    queue->cur_level.rate_time =
        queue->cur_level.bytes / queue->byte_in_rate * GST_SECOND;
  }
  GST_DEBUG_OBJECT (queue, "rates: in %f, time %" GST_TIME_FORMAT,
      queue->byte_in_rate, GST_TIME_ARGS (queue->cur_level.rate_time));
}
