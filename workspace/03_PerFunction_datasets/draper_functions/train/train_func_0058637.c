multisumnsteps(node *p, node *q, long a, long b, long *threshwt)
{

  long i, j, steps, largest, descsteps, purset, pyrset, b1;
  long term;

  if (a == 0) p->sumsteps = 0.0;
  purset = (1 << (long)A) + (1 << (long)G);
  pyrset = (1 << (long)C) + (1 << (long)T);
  for (i = a; i < b; i++) {
    descsteps = 0;
    for (j = (long)A; j <= (long)O; j++) {
      if ((descsteps == 0) && (p->base[i] & (1 << j)))
        descsteps = p->numsteps[i] -
                        (p->numdesc - 1 - p->numnuc[i][j]) * weight[i];
    }
    descsteps += q->numsteps[i];
    largest = 0;
    for (j = (long)A; j <= (long)O; j++) {
      b1 = (1 << j);
      if (transvp) {
        if (b1 & purset) b1 = purset;
        if (b1 & pyrset) b1 = pyrset;
      }
      if (q->base[i] & b1)
        p->numnuc[i][j]++;
      if (p->numnuc[i][j] > largest)
        largest = p->numnuc[i][j];
    }
    steps = (p->numdesc - largest) * weight[i] + descsteps;
    if ((long)steps <= threshwt[i])
      term = steps;
    else
      term = threshwt[i];
    p->sumsteps += (double)term;
  }
}
