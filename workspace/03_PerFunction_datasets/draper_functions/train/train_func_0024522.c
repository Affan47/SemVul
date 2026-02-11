cloneOnScratch(ChessGame *cg0) {
  Board *b;
  ChessGame *cg;
  char z[64];
  int id;

  id = global.nextFreeGameId(30000);
  cg=new ChessGame(cg0);
  cg->GameNumber = id;
  cg->LocalEdit = true;
  cg->source = GS_Other;

  global.appendGame(cg,false);
  b=new EditBoard(cg);
  cg->setBoard(b);
  cg->StopClock = 1;

  snprintf(z,64,_("Scratch %d"),++global.LastScratch);
  notebook->addPage(b->widget,z,id);
  b->setNotebook(notebook,id);
  notebook->goToPageId(id);
  b->update();
}
