ffwdOk(void *packet)  {
  CliBoard  *cli = packet;

  assert(MAGIC(cli));
  return((cli->game->moveNum < cli->game->maxMoves) ||
	 (cli->gameEnd != cli->sgf->active));
}
