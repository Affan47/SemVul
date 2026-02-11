color_matrix_multiply (ColorMatrix * dst, ColorMatrix * a, ColorMatrix * b)
{
  ColorMatrix tmp;
  int i, j, k;

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      double x = 0;
      for (k = 0; k < 4; k++) {
        x += a->m[i][k] * b->m[k][j];
      }
      tmp.m[i][j] = x;
    }
  }

  memcpy (dst, &tmp, sizeof (ColorMatrix));
}
