event_cache_add_for_players(const struct packet_chat_msg *packet,
                                 struct event_cache_players *players)
{
  if (0 < game.server.event_cache.turns
      && NULL != players
      && BV_ISSET_ANY(players->vector)
      && (server_state() > S_S_INITIAL || !game.info.is_new_game)) {
    (void) event_cache_data_new(packet, game.info.turn, time(NULL),
                                server_state(), ECT_PLAYERS, players);
  }

  if (NULL != players) {
    free(players);
  }
}
