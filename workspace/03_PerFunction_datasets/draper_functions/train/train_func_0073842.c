quadtoPL(int sel, Quad *q, va_list *args) {
  PLData *PL = va_arg(*args, PLData *);
  int base, v, i;

  base = PLaddverts(PL, q->maxquad*4, *q->p, *q->c, *q->n);
  for(i = 0, v = base; i < q->maxquad; i++) {
    int face[4];
    face[0] = v++;
    face[1] = v++;
    face[2] = v++;
    face[3] = v++;
    PLaddface(PL, 4, face, NULL);
  }
  return PL;
}
