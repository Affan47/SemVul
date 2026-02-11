plottree(node *p, node *q)
{

  double x1, y1, x2, y2;
  node *pp;

  x2 = xscale * (xoffset + p->xcoord);
  y2 = yscale * (yoffset + p->ycoord);
  if (p != root) {
    x1 = xscale * (xoffset + q->xcoord);
    y1 = yscale * (yoffset + q->ycoord);
    plot(penup, x1, y1);
    plot(pendown, x2, y2);
  }
  if (p->tip)
    return;
  pp = p->next;
  do {
    plottree(pp->back, p);
    pp = pp->next;
  } while (((p == root) && (pp != p->next)) || ((p != root) && (pp != p)));
}
