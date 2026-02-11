vc_identity_p (gdouble ** matrx, gint n)
{
  gint i, j;
  gboolean retn_val = true;
  gfloat tol = 0.001;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if ((i == j) && (fabs ((1.000 - matrx[i][j])) > tol)) {
        retn_val = false;
        break;
      }
      else if ((i != j) && (fabs (matrx[i][j]) > tol)) {
        retn_val = false;
        break;
      }
    }
  }
  return (retn_val);
}
