dai_player_free(struct player *pplayer)
{
  struct ai_plr *player_data = def_ai_player_data(pplayer);

  ai_data_close(pplayer);

  if (player_data != NULL) {
    player_set_ai_data(pplayer, default_ai_get_self(), NULL);
    FC_FREE(player_data);
  }
}
