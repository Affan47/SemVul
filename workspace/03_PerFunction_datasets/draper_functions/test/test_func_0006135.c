innerRemoveGame(int gameid) {
  Board *b;
  ChessGame *cg;

  cg=global.getGame(gameid);
  if (cg==NULL)
    return;


  if (cg->protodata[2])
    global.bugpane->stopClock();

  b=cg->getBoard();
  if (b==NULL) return;
  global.ebook->removePage(gameid);
  global.removeBoard(b);
  delete(b);
  cg->GameNumber=global.nextFreeGameId(10000);
  cg->setBoard(0);
}
