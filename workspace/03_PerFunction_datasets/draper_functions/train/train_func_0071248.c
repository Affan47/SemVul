tfrc_receiver_free (TfrcReceiver *receiver)
{
  ReceivedInterval *ri;

  while ((ri = g_queue_pop_tail (&receiver->received_intervals)))
    g_slice_free (ReceivedInterval, ri);

  g_slice_free (TfrcReceiver, receiver);
}
