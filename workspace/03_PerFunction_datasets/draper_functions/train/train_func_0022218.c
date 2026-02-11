newScratchBoard(bool clearboard) {
  Board *b;
  ChessGame *cg;
  Position *p;
  int id,i,j;
  char z[64];

  id = global.nextFreeGameId(30000);

  cg=new ChessGame(id, 0, 0, 0, REGULAR,
		   "Nobody","Nessuno");
  cg->LocalEdit=true;

  global.appendGame(cg,false);
  b=new EditBoard(cg);
  cg->setBoard(b);
  cg->StopClock = 1;

  snprintf(z,64,_("Scratch %d"),++global.LastScratch);
  notebook->addPage(b->widget,z,id);
  b->setNotebook(notebook,id);

  p=new Position();
  if (clearboard)
    for(i=0;i<8;i++)
      for(j=0;j<8;j++)
	p->setPiece(i,j,EMPTY);

  cg->updatePosition2(*p,1,0,0,0,_("<editing>"),false);
  notebook->goToPageId(id);
}
