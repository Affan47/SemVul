solveB1(longDouble * a, int n, CoinWorkDouble * region)
{
     int j, k;
     CoinWorkDouble t00;
     for (j = n - 1; j >= 0; j --) {
          t00 = region[j];
          for (k = j + 1; k < n; ++k) {
               t00 -= region[k] * a[k + j * BLOCK];
          }

          region[j] = t00;
     }
}
