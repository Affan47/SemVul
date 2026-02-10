gameWalk(int op) {
  Board *b=0;
  ChessGame *cg=0;
  int id;

  global.debug("MainWindow","gameWalk");

  id=notebook->getCurrentPageId();

  if (id<=-2)
    return;

  if (id==-1)
    b=global.BoardList.front();
  else {
    cg=global.getGame(id);
    if (cg)
      b=cg->getBoard();
  }

  if (!b)
    return;


  if (cg)
    if (cg->protodata[0]==258) {
      switch(op) {
      case 0: global.protocol->exaBackward(999); return;
      case 1: global.protocol->exaBackward(1); return;
      case 2: global.protocol->exaForward(1); return;
      case 3: global.protocol->exaForward(999); return;
      }
    }

  switch(op) {
  case 0: b->walkBackAll(); break;
  case 1: b->walkBack1(); break;
  case 2: b->walkForward1(); break;
  case 3: b->walkForwardAll(); break;
  case 4: b->openMovelist(); break;
  case 5:
    if ((id<=0)||(!cg)) break;
    if ( (cg->protodata[1]) || ( ! global.protocol ) || (cg->LocalEdit) ) {
      cg->protodata[1]=0;
      global.ebook->removePage(cg->GameNumber);
      global.removeBoard(b);
      delete(b);
      cg->setBoard(NULL);
      if (cg->LocalEdit)
	global.deleteGame(cg);
    } else {
      if ((id>0)&&(global.protocol!=NULL))
	global.protocol->discardGame(cg->GameNumber);
    }
    break;
  case 6:
    b->setFlipInversion(!b->getFlipInversion());
    break;
  case 7:
    cloneOnScratch(b->getGame());
    break;
  }
}
