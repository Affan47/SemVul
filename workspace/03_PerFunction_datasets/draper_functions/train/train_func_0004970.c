fdescribe(FILE *fp, node *p)
{

  double sumlr;
  long i;
  node *q;
  double s;
  double realv;

  q = p->back;
  fprintf(fp, "%4ld      ", q->index - spp);
  fprintf(fp, "    ");
  if (p->tip) {
    for (i = 0; i < nmlngth; i++)
      putc(nayme[p->index - 1][i], fp);
  } else
    fprintf(fp, "%4ld      ", p->index - spp);
  if (q->v >= 0.75)
    fprintf(fp, "     infinity");
  else {
    realv = -0.75 * log(1 - 4.0/3.0 * q->v);
    fprintf(fp, "%13.5f", realv);
  }
  if (p->iter) {
    s = sigma(q, &sumlr);
    if (s < 0.0)
      fprintf(fp, "     (     zero,    infinity)");
    else {
      fprintf(fp, "     (");
      if (q->v - s <= 0.0)
        fprintf(fp, "     zero");
      else
        fprintf(fp, "%9.5f", -0.75 * log(1 - 1.333333 * (q->v - s)));
      putc(',', fp);
      if (q->v + s >= 0.75)
        fprintf(fp, "    infinity");
      else
        fprintf(fp, "%12.5f", -0.75 * log(1 - 1.333333 * (q->v + s)));
      putc(')', fp);
      }
    if (sumlr > 1.9205)
      fprintf(fp, " *");
    if (sumlr > 2.995)
      putc('*', fp);
    }
  else
    fprintf(fp, "            (not varied)");
  putc('\n', fp);
  if (!p->tip) {
    for (q = p->next; q != p; q = q->next)
      fdescribe(fp, q->back);
  }
}
