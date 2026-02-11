shiftqr(double (*a)[20], long n, double accuracy)
{
  long i, j;
  double approx, s, c, d, TEMP, TEMP1;

  for (i = n; i >= 2; i--) {
    do {
      TEMP = a[i - 2][i - 2] - a[i - 1][i - 1];
      TEMP1 = a[i - 1][i - 2];
      d = sqrt(TEMP * TEMP + TEMP1 * TEMP1);
      approx = a[i - 2][i - 2] + a[i - 1][i - 1];
      if (a[i - 1][i - 1] < a[i - 2][i - 2])
        approx = (approx - d) / 2.0;
      else
        approx = (approx + d) / 2.0;
      for (j = 0; j < i; j++)
        a[j][j] -= approx;
      for (j = 1; j < i; j++) {
        coeffs(a[j - 1][j - 1], a[j][j - 1], &c, &s, accuracy);
        givens(a, j, j + 1, i, c, s, true);
        givens(a, j, j + 1, i, c, s, false);
        givens(eigvecs, j, j + 1, n, c, s, true);
      }
      for (j = 0; j < i; j++)
        a[j][j] += approx;
    } while (fabs(a[i - 1][i - 2]) > accuracy);
  }
}
