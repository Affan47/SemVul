increase_maxbuycost(struct player *pplayer, int new_value)
{
  pplayer->ai_common.maxbuycost = MAX(pplayer->ai_common.maxbuycost, new_value);
}
