player_by_user(const char *name)
{
  players_iterate(pplayer) {
    if (fc_strcasecmp(name, pplayer->username) == 0) {
      return pplayer;
    }
  } players_iterate_end;

  return NULL;
}
