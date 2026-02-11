tfrc_receiver_send_feedback (TfrcReceiver *receiver, guint64 now,
    double *loss_event_rate, guint *receive_rate)
{
  guint received_bytes;
  guint64 received_bytes_reset_time;
  guint received_packets;

  if (now == receiver->prev_received_bytes_reset_time)
    return FALSE;

  if (now - receiver->received_bytes_reset_time >
      receiver->sender_rtt_on_last_feedback ) {
    receiver->prev_received_bytes_reset_time =
        receiver->received_bytes_reset_time;
    receiver->prev_received_bytes = receiver->received_bytes;
    receiver->prev_received_packets = receiver->received_packets;
    received_bytes = receiver->received_bytes;
    received_packets = receiver->received_packets;
    received_bytes_reset_time = receiver->received_bytes_reset_time;
  } else {
    receiver->prev_received_bytes += receiver->received_bytes;
    receiver->prev_received_packets += receiver->received_packets;
    received_bytes = receiver->prev_received_bytes;
    received_packets = receiver->prev_received_packets;
    received_bytes_reset_time = receiver->prev_received_bytes_reset_time;
  }

  receiver->received_bytes_reset_time = now;
  receiver->received_bytes = 0;
  receiver->received_packets = 0;

  receiver->receive_rate = gst_util_uint64_scale_round (SECOND, received_bytes,
      now - received_bytes_reset_time);

  if (receiver->sender_rtt_on_last_feedback &&
      receiver->receive_rate > receiver->max_receive_rate)
  {
    receiver->max_receive_rate = receiver->receive_rate;
    receiver->max_receive_rate_ss = received_bytes / received_packets;
  }

  receiver->loss_event_rate = calculate_loss_event_rate (receiver, now);

  if (receiver->sender_rtt)
    receiver->feedback_timer_expiry = now + receiver->sender_rtt;
  receiver->sender_rtt_on_last_feedback = receiver->sender_rtt;
  receiver->feedback_sent_on_last_timer = TRUE;

  DEBUG_RECEIVER (receiver, "P: %f recv_rate: %u", receiver->loss_event_rate,
      receiver->receive_rate);

  *receive_rate = receiver->receive_rate;
  *loss_event_rate = receiver->loss_event_rate;

  return TRUE;
}
