matrix_inv_vandermonde(gf *a, int k) {


  if (k == 1)
    return 0;


  gf p[k];


  gf c[k];
  int i, j;
  for (i = 0, j = 1; i < k; i++, j += k) {
    c[i] = 0;
    p[i] = a[j];
  }


  c[k-1] = p[0];
  for (i = 1; i < k; i++) {
    gf p_i = p[i];


    for (j = k - 1 - i; j < k - 1; j++)
      c[j] = GF_ADD(c[j], GF_MUL(p_i, c[j+1]));
    c[k-1] = GF_ADD(c[k-1], p_i);
  }


  gf b[k];


  int row;
  for (row = 0; row < k; row++) {
    gf x = p[row];
    gf t = 1;

    b[k-1] = 1;
    for (i = k - 2; i >= 0; i--) {
      b[i] = GF_ADD(c[i+1], GF_MUL(x, b[i+1]));
      t = GF_ADD(GF_MUL(x, t), b[i]);
    }

    int col;
    for (col = 0; col < k; col++)
      a[col * k + row] = GF_MUL(GF_INV(t), b[col]);
  }

  return 1;
}
