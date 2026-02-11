fun(f, x)
double *f;
double *x;
{
  int i, k;

  k = 0;
  for (i = 0; i < nall; i++) {
    if (itp[i] == 1) {
      k++;
      xall[i] = x[k - 1];
    }
  }

  setparam();
  if (penalty) {
    *f = 1.5 * penlike;
    return;
  }
  for (i = 1; i <= totperson; i++) {
    person[i]->done = false;
    person[i]->firstpass = true;
  }
  recombination();
  alike = 0.0;
  thisc = minint;
  for (i = 1; i <= nuped; i++) {
    likelihood(i, proband[i - 1]);
    alike += like;
    likebyped[i-1] = like;
  }
  if (firsttime) {
    if (thisc < maxcensor)
      printf("Maxcensor can be reduced to %12d\n", thisc);
    else {
      if (thisc > maxcensor)
	printf("You may gain efficiency by increasing maxcensor\n");
    }
  }
  firsttime = false;
  *f = -2 * alike;
  penlike = *f;
  firsttime = false;
}
