searchInBM(char *x, int m, char *y, int n, int * addr) {
  int i, j, bmGs[m], bmBc[CACHESIZE];


  preBmGs(x, m, bmGs);
  preBmBc(x, m, bmBc);


  j = 0;
  while (j <= n - m) {
    for (i = m - 1; i >= 0 && x[i] == y[i + j]; --i);
    if (i < 0) {

      *addr += (1 << j);
      j += bmGs[0];
    }
    else
      j += max(bmGs[i], bmBc[y[i + j]-'0'] - m + 1 + i);
  }
}
