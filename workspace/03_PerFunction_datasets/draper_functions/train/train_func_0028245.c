isPrime(int i) {
  int t;

  if (i < 2) {
    return FALSE;
  }
  if (i == 2) {
    return TRUE;
  }
  if (i % 2 == 0) {
    return FALSE;
  }
  t = 3;
  while (t * t <= i) {
    if (i % t == 0) {
      return FALSE;
    }
    t += 2;
  }
  return TRUE;
}
