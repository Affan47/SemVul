_dist(struct state *st, int x1, int x2, int y1, int y2, int s)
{
  double xd=x1-x2;
  double yd=y1-y2;
  switch(s) {
    case 0:
      return((int)sqrt(xd*xd+yd*yd));
    case 1:
      return((int)sqrt(xd*xd*st->cs1[0]*2+yd*yd));
    case 2:
      return((int)sqrt(xd*xd+yd*yd*st->cs2[0]*2));
    default:
      return((int)sqrt(xd*xd*st->cs1[0]/st->cs2[0]+yd*yd*st->cs3[0]/st->cs4[0]));
  }
}
