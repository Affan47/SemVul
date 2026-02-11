describe(node *p)
{

  long i=0;
  node *q;

  q = p->back;
  fprintf(outfile, "%4ld          ", q->index - spp);
  if (p->tip) {
    for (i = 0; i < nmlngth; i++)
      putc(nayme[p->index - 1][i], outfile);
  } else
    fprintf(outfile, "%4ld      ", p->index - spp);
  fprintf(outfile, "%15.5f\n", q->v);
  if (!p->tip) {
    describe(p->next->back);
    describe(p->next->next->back);
  }
}
