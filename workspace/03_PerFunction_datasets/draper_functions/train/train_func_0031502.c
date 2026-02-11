coordinates(node *p, double lengthsum, long *tipy, double *tipmax,
                        node *start, boolean njoin)
{

  node *q, *first, *last;

  if (p->tip) {
    p->xcoord = (long)(over * lengthsum + 0.5);
    p->ycoord = *tipy;
    p->ymin = *tipy;
    p->ymax = *tipy;
    (*tipy) += down;
    if (lengthsum > *tipmax)
      *tipmax = lengthsum;
    return;
  }
  q = p->next;
  do {
    if (q->back)
      coordinates(q->back, lengthsum + q->v, tipy,tipmax, start, njoin);
    q = q->next;
  } while ((p == start || p != q) && (p != start || p->next != q));
  first = p->next->back;
  q = p;
  while (q->next != p && q->next->back)
    q = q->next;
  last = q->back;
  p->xcoord = (long)(over * lengthsum + 0.5);
  if (p == start && p->back)
    p->ycoord = p->next->next->back->ycoord;
  else
    p->ycoord = (first->ycoord + last->ycoord) / 2;
  p->ymin = first->ymin;
  p->ymax = last->ymax;
}
