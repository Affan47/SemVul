drawPiece(piece p,rgbptr dest,int x,int y,int dwidth) {
  int sx=0, sy=0;
  int top, sc=0, hlt=0;
  p&=CUTFLAGS;
  if (p==EMPTY) return;

  if (queuef) {
    queueRequest(new PReq(p,dest,x,y,dwidth,false));
    return;
  }

  if (p&BLACK)  sy=height;
  sx=side*((p&PIECE_MASK)-1);

  if (extruded) {
    if (bottom_only) {
      sc=height-side; top=y;
    } else {
      top=y-(height-side);
      if (top < 0) { sc = -top; top=0; }
    }

    if (top_only) hlt=height-side;
    if (sc<height)
      bitblt_a(isrc->data,dest,
	       sx,sy+sc,7*side,
	       x,top,dwidth,
	       side,height-sc-hlt,alphamask);
  } else
    bitblt_a(isrc->data,dest,sx,sy,7*side,x,y,dwidth,side,side,alphamask);
}
