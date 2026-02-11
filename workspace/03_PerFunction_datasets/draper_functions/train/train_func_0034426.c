lsend_vote_resolve(struct conn_list *dest,
                               struct vote *pvote, bool passed)
{
  struct packet_vote_resolve packet;

  if (!pvote) {
    return;
  }

  packet.vote_no = pvote->vote_no;
  packet.passed = passed;

  if (dest == NULL) {
    dest = game.est_connections;
  }

  conn_list_iterate(dest, pconn) {
    if (!conn_can_see_vote(pconn, pvote)) {
      continue;
    }
    send_packet_vote_resolve(pconn, &packet);
  } conn_list_iterate_end;
}
