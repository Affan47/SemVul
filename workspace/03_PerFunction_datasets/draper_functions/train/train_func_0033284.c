hashseq_skip_revcomp (char *sequence, int length1, int skip, int length2) {
  int sum = 0;
  int i, digit;

  for (i = length1+skip+length2; i > length1+skip; i--) {
    switch (sequence[i]) {
    case 'A': case 'a': digit = 3; break;
    case 'C': case 'c': digit = 2; break;
    case 'G': case 'g': digit = 1; break;
    case 'T': case 't': digit = 0; break;
    default: digit = 3;

    }
    debug1(printf(" %d",digit));
    sum = sum*4 + digit;
  }

  for (i = length1; i > 0; i--) {
    switch (sequence[i]) {
    case 'A': case 'a': digit = 3; break;
    case 'C': case 'c': digit = 2; break;
    case 'G': case 'g': digit = 1; break;
    case 'T': case 't': digit = 0; break;
    default: digit = 3;

    }
    debug1(printf(" %d",digit));
    sum = sum*4 + digit;
  }

  debug1(printf("\n"));
  return sum;
}
