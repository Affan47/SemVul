palaRotate(struct state *st, int x,int y)
{
  int ax,ay,bx,by,cx,cy;

  ax=st->rotateX[x];
  ay=st->rotateY[y];
  bx=st->rotateX[x+1]+2;
  by=st->rotateY[y+1]+2;
  cx=st->rotateX[x]-(y-st->ry)+x-st->rx;
  cy=st->rotateY[y]+(x-st->rx)+y-st->ry;
  if (cx<0)
    {
      ax-=cx;
      cx=0;
    }
  if (cy<0)
    {
      ay-=cy;
      cy=0;
    }
  if (cx+bx-ax>st->sizx) bx=ax-cx+st->sizx;
  if (cy+by-ay>st->sizy) by=ay-cy+st->sizy;
  if (ax<bx && ay<by)
    XCopyArea(st->dpy,st->win[0],st->win[1],st->cgc,ax,ay,bx-ax,by-ay,cx,cy);
}
