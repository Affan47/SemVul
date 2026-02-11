send_player_info_c(struct player *src, struct conn_list *dest)
{
  if (0 < player_info_frozen_level) {
    return;
  }

  if (src != NULL) {
    send_player_info_c_real(src, dest);
    return;
  }

  players_iterate(pplayer) {
    send_player_info_c_real(pplayer, dest);
  } players_iterate_end;
}
