sumnsteps2(node *p,node *left,node *rt,long a,long b,long *threshwt)
{

  long i, steps;
  long ns, rs, ls, purset, pyrset;
  long term;

  if (a == 0) p->sumsteps = 0.0;
  if (!left)
    memcpy(p->numsteps, rt->numsteps, endsite*sizeof(long));
  else if (!rt)
    memcpy(p->numsteps, left->numsteps, endsite*sizeof(long));
  else {
    purset = (1 << (long)A) + (1 << (long)G);
    pyrset = (1 << (long)C) + (1 << (long)T);
    for (i = a; i < b; i++) {
      ls = left->base[i];
      rs = rt->base[i];
      ns = ls & rs;
      p->numsteps[i] = left->numsteps[i] + rt->numsteps[i];
      if (ns == 0) {
        ns = ls | rs;
        if (transvp) {
          if (!((ns == purset) || (ns == pyrset)))
            p->numsteps[i] += weight[i];
        }
        else p->numsteps[i] += weight[i];
      }
    }
  }
  for (i = a; i < b; i++) {
    steps = p->numsteps[i];
    if ((long)steps <= threshwt[i])
      term = steps;
    else
      term = threshwt[i];
    p->sumsteps += (double)term;
  }
}
