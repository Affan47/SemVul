reconstr(node *p, long n)
{

  long i, j, k, m, first, second, num_sibs;
  double f, sum, xx[4];
  node *q;

  if ((ally[n] == 0) || (location[ally[n]-1] == 0))
    putc('.', outfile);
  else {
    j = location[ally[n]-1] - 1;
    for (i = 0; i < 4; i++) {
      f = p->x[j][mx-1][i];
      num_sibs = count_sibs(p);
      q = p;
      for (k = 0; k < num_sibs; k++) {
        q = q->next;
        f *= q->x[j][mx-1][i];
      }
      f = sqrt(f);
      xx[i] = f;
    }
    xx[0] *= freqa;
    xx[1] *= freqc;
    xx[2] *= freqg;
    xx[3] *= freqt;
    sum = xx[0]+xx[1]+xx[2]+xx[3];
    for (i = 0; i < 4; i++)
      xx[i] /= sum;
    first = 0;
    for (i = 1; i < 4; i++)
      if (xx [i] > xx[first])
        first = i;
    if (first == 0)
      second = 1;
    else
      second = 0;
    for (i = 0; i < 4; i++)
      if ((i != first) && (xx[i] > xx[second]))
        second = i;
    m = 1 << first;
    if (xx[first] < 0.4999995)
      m = m + (1 << second);
    if (xx[first] > 0.95)
      putc(toupper((int)basechar[m - 1]), outfile);
    else
      putc(basechar[m - 1], outfile);
    if (rctgry && rcategs > 1)
      mx = mp[n][mx - 1];
    else
      mx = 1;
  }
}
