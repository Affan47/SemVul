pieceSetChanged() {
 if (cur)
    delete cur;
  cur=new PieceSet(global.pieceset);
  currently_rendered.invalidate();
  if (global.ShowCoordinates) { borx=20; bory=20; } else { borx=bory=0; }
  morey=0;
  UpdateClockAfterConfigure = true;
  queueRepaint();
}
