pow2(int x) {
  double r=1;
  for (; x>0; x--) r+=r;
  return r;
}
