discardGame(int gameid) {
  ChessGame *cg;
  Board *b;
  char z[64];

  global.debug("FicsProtocol","discardGame");

  cg=global.getGame(gameid);
  if (!cg)
    return;

  switch(cg->protodata[0]) {
  case 257:
    snprintf(z,64,"unobserve %d",cg->GameNumber);
    break;
  case 258:
    strcpy(z,"unexamine");
    break;
  case 259:
    z[0]=0;
    break;
  default:
    cerr << "protodata for game " << gameid << " is " << cg->protodata[0] << endl;
    return;
  }

  if (! cg->isOver())
    if (strlen(z))
      global.network->writeLine(z);

  b=cg->getBoard();
  if (b==0) return;
  global.ebook->removePage(cg->GameNumber);
  global.removeBoard(b);
  delete(b);
  cg->GameNumber=global.nextFreeGameId(10000);
  cg->setBoard(0);

}
