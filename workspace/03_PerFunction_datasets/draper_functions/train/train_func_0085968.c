createGame() {
  ChessGame *cg;
  Position *pos;
  global.debug("XBoardProtocol","createGame");

  MoveNumber=1;
  MoveBlack=0;

  cg=new ChessGame();
  cg->GameNumber=XBOARD_GAME;
  cg->source = GS_Engine;
  cg->timecontrol = timecontrol;
  g_strlcpy(cg->PlayerName[EngineWhite?0:1],getComputerName(),64);
  g_strlcpy(cg->PlayerName[EngineWhite?1:0],global.env.User.c_str(),64);

  cg->MyColor=EngineWhite?BLACK:WHITE;

  timecontrol.toString(cg->info0,64);

  cg->clock_regressive=timecontrol.isRegressive()?1:0;
  cg->Rated=0;
  cg->Variant=Variant;
  global.appendGame(cg);
  global.BoardList.front()->reset();
  cg->setBoard(global.BoardList.front());
  global.BoardList.front()->setGame(cg);
  global.BoardList.front()->pop();
  global.BoardList.front()->setCanMove(true);
  global.BoardList.front()->repaint();
  if (EngineWhite)
    global.BoardList.front()->setFlipped(true);
  cg->acknowledgeInfo();
  cg->fireWhiteClock(timecontrol.startValue(),
		     timecontrol.startValue());

  pos=new Position();

  if (got_init_pos) {
    (*pos)=initpos;
    CurrentPosition = initpos;
    LegalityBackup  = initpos;
    MoveBlack = pos->sidehint ? 0 : 1;
  }

  cg->updatePosition2(*pos,1,pos->sidehint ? 0:1,
		      1000*timecontrol.startValue(),
		      1000*timecontrol.startValue(),
		      "0. startpos");
  delete pos;

  global.gameStarted();
}
