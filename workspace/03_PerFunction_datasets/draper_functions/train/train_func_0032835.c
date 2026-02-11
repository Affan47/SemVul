goGame_moveTo(GoGame *game, int moveNum)  {
  bool  newState = FALSE;
  int  oldSetColorMove;

  assert(MAGIC(game));
  assert(moveNum >= 0);
  assert(game->passive || game->forcePlay ||
	 ((game->state == goGameState_play) ||
	  (game->state == goGameState_done) ||
	  (game->state == goGameState_dispute)));
  assert((game->state != goGameState_dispute) ||
	 (moveNum >= game->setWhoseMoveNum));
  assert(moveNum <= game->maxMoves);
  game->moveNum = moveNum;
  oldSetColorMove = game->setWhoseMoveNum;
  goGame_replay(game, game->moveNum, FALSE);
  if ((game->state == goGameState_dispute) &&
      (game->moveNum >= oldSetColorMove))
    game->setWhoseMoveNum = oldSetColorMove;
  if ((game->state == goGameState_play) && (game->passCount == 2) &&
      !game->passive && !game->forcePlay)  {
    newState = TRUE;
    game->state = goGameState_done;
  } else if ((game->state == goGameState_done) && (game->passCount < 2)
	     && !game->passive && !game->forcePlay)  {
    newState = TRUE;
    game->state = goGameState_play;
  }
  return(newState);
}
