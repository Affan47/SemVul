composeVecBoard(GdkGC *gc) {
  Position *joker;
  int i,j;
  global.vpieces.drawSquares(buffer,gc,sqside, borx, bory);

  if (gotAnimationLoop) joker=&fake; else joker=&position;
  if (effectiveFlip())
    for(i=0;i<8;i++)
      for(j=0;j<8;j++)
	global.vpieces.drawPiece(buffer,gc,sqside,borx+i*sqside,bory+j*sqside,
				 joker->getPiece(7-i,j));
  else
    for(i=0;i<8;i++)
      for(j=0;j<8;j++)
	global.vpieces.drawPiece(buffer,gc,sqside,borx+i*sqside,bory+j*sqside,
				 joker->getPiece(i,7-j));

  if (global.ShowCoordinates)
    drawCoordinates(buffer,gc,sqside);

  i=Width();
  gdk_rgb_gc_set_foreground(gc,0);
  gdk_draw_rectangle(buffer,gc,TRUE,0,i,i,sqh-Height());

  currently_rendered=*(joker);
}
