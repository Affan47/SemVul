evaluate(node *r)
{


  long i, steps, term;
  double sum;

  sum = 0.0;
  for (i = 0; i < (chars); i++) {
    steps = r->numsteps[i];
    if (steps <= threshwt[i])
      term = steps;
    else
      term = threshwt[i];
    sum += term;
    if (usertree && which <= maxuser)
      fsteps[which - 1][i] = term;
  }
  if (usertree && which <= maxuser) {
    nsteps[which - 1] = sum;
    if (which == 1) {
      minwhich = 1;
      minsteps = sum;
    } else if (sum < minsteps) {
      minwhich = which;
      minsteps = sum;
    }
  }
  like = -sum;
}
