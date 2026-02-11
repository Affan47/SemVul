single_rotate(JRB y, int l)
{
  int rl = 0, ir;
  JRB x, yp;

  ir = isroot(y);
  yp = y->parent;
  if (!ir) {
    rl = isleft(y);
  }

  if (l) {
    x = y->flink;
    y->flink = x->blink;
    setleft(y->flink);
    y->flink->parent = y;
    x->blink = y;
    setright(y);
  } else {
    x = y->blink;
    y->blink = x->flink;
    setright(y->blink);
    y->blink->parent = y;
    x->flink = y;
    setleft(y);
  }

  x->parent = yp;
  y->parent = x;
  if (ir) {
    yp->parent = x;
    setnormal(y);
    setroot(x);
  } else {
    if (rl) {
      yp->flink = x;
      setleft(x);
    } else {
      yp->blink = x;
      setright(x);
    }
  }
}
