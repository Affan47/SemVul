editEmpty() {
  Position p;
  int i,j;

  if (!LocalEdit) return;

  moves.clear();
  last_half_move=1;

  for(i=0;i<8;i++) for(j=0;j<8;j++) p.setPiece(i,j,EMPTY);
  p.sidehint=true;

  moves.push_back(p);
  cursor=moves.end();
  cursor--;
  if (myboard) {
    myboard->setInfo(2,(*cursor).getLastMove());
    myboard->setInfo(4,p.getMaterialString());
    myboard->update();
  }
}
