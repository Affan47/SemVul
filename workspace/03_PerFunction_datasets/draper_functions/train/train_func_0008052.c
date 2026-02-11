sendDrop(piece p,int x,int y) {
  ChessGame *refgame;
  char mymove[12],ppfmm[32];
  piece clp;

  refgame=getGame();
  LegalityBackup=CurrentPosition;

  snprintf(mymove,12,"P@%c%c",'a'+x,'1'+y);
  clp=p&PIECE_MASK;
  switch(clp) {
  case PAWN:    mymove[0]='P'; break;
  case ROOK:    mymove[0]='R'; break;
  case KNIGHT:  mymove[0]='N'; break;
  case BISHOP:  mymove[0]='B'; break;
  case QUEEN:   mymove[0]='Q'; break;
  case KING:    mymove[0]='K'; break;
  }
  CurrentPosition.moveDrop(p|(refgame->MyColor),x,y);

  if (EngineWhite)
    snprintf(ppfmm,32,"%d. ... %s",MoveNumber,mymove);
  else
    snprintf(ppfmm,32,"%d. %s",MoveNumber,mymove);

  refgame->updatePosition2(CurrentPosition,
			   MoveNumber,!MoveBlack,
			   CLOCK_UNCHANGED,
			   CLOCK_UNCHANGED,
			   ppfmm);

  global.network->writeLine(mymove);
  advanceMove();
  global.BoardList.front()->setCanMove(false);
}
