prime(int n)
{


  static BOOL a[MAX_PRIME+1];
  static BOOL initialized = FALSE;

  if (!initialized) {
    int i, p;
    for (i = 2; i <= MAX_PRIME; i++)
      a[i] = TRUE;
    p = 2;
    while (p*p < MAX_PRIME) {
      int j = p*p;
      while (j  < MAX_PRIME) {
	a[j] = FALSE;
	j = j + p;
      }
      do p++; while (a[p] == FALSE);
    }
    initialized = TRUE;
  }
  if (n > MAX_PRIME)
    exit(1);
  else if (n < 2)
    return FALSE;
  else
    return a[n];
}
