putinterval (double *poly, int degree, double *nvec, int last, double *nscale,
	     int nlen, double oval, int sign)
{
  int end, i;


  for (end = last + 1; end < nlen; end++)
    if (nscale[end] * sign > oval * sign)
      break;
  end--;

  for (i = last + 1; i <= end; i++)
    nvec[i] = ft_peval (nscale[i], poly, degree);
  return (end);
}
