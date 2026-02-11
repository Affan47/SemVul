makenewv(node *p)
{

  long it, ite;
  double y, yold=0, yorig, like, slope, curve, oldlike=0;
  boolean done, firsttime, better;
  node *q;

  q = p->back;
  y = p->v;
  yorig = y;
  done = false;
  firsttime = true;
  it = 1;
  ite = 0;
  while ((it < iterations) && (ite < 20) && (!done)) {
    slopecurv (p, y, &like, &slope, &curve);
    better = false;
    if (firsttime) {
      yold = y;
      oldlike = like;
      firsttime = false;
      better = true;
    } else {
      if (like > oldlike) {
        yold = y;
        oldlike = like;
        better = true;
        it++;
      }
    }
    if (better) {
      y = y + slope/fabs(curve);
      if (y < epsilon)
        y = epsilon;
    } else {
      if (fabs(y - yold) < epsilon)
        ite = 20;
      y = (y + 19*yold) / 20.0;
    }
    ite++;
    done = fabs(y-yold) < 0.1*epsilon;
  }
  smoothed = (fabs(yold-yorig) < epsilon) && (yorig > 1000.0*epsilon);
  p->v = yold;
  q->v = yold;
  curtree.likelihood = oldlike;
}
