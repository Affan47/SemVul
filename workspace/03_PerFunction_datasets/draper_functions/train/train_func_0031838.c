gram_schmidt(gdouble *x1, gdouble *x2, gint n)
{
  gint j;
  gdouble ip;
  gdouble tol=0.99;
  gboolean ok = true;

  ip = inner_prod(x1, x2, n);

  if (fabs(ip) < tol) {
    for (j=0; j<n; j++)
      x2[j] = x2[j] - ip*x1[j];
    norm(x2, n);
  }
  else if (fabs(ip) > 1.0-tol)
    ok = false;

  return(ok);
}
