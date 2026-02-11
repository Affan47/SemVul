reliable_ack_packet_id_present (struct reliable_ack *ack, packet_id_type pid)
{
  int i;
  for (i = 0; i < ack->len; ++i)
    if (ack->packet_id[i] == pid)
      return true;
  return false;
}
