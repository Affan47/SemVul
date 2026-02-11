rectrav(node *p, long m, long n)
{

  long i;
  node *q;

  putc(' ', outfile);
  if (p->tip) {
    for (i = 0; i < nmlngth; i++)
      putc(nayme[p->index-1][i], outfile);
  } else
    fprintf(outfile, "%4ld      ", p->index - spp);
  fprintf(outfile, "  ");
  mx = mx0;
  for (i = m; i <= n; i++) {
    if ((i % 10 == 0) && (i != m))
      putc(' ', outfile);
    prot_reconstr(p, i);
  }
  putc('\n', outfile);
  if (!p->tip)
    for ( q = p->next; q != p; q = q->next )
      rectrav(q->back, m, n);
  mx1 = mx;
}
