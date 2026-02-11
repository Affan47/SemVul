backOk(void *packet)  {
  EditBoard  *e = packet;

  assert(MAGIC(e));
  return((e->game->state == goGameState_play) && (e->currentNodeNum > 0));
}
