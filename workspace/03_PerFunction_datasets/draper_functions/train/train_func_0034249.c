conn_reset_delta_state(struct connection *pc)
{
  int i;

  for (i = 0; i < PACKET_LAST; i++) {
    if (packet_has_game_info_flag(i)) {
      if (NULL != pc->phs.sent && NULL != pc->phs.sent[i]) {
        genhash_clear(pc->phs.sent[i]);
      }
      if (NULL != pc->phs.received && NULL != pc->phs.received[i]) {
        genhash_clear(pc->phs.received[i]);
      }
    }
  }
}
