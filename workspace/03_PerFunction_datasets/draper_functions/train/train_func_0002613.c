fnorm_sqr()
{
  int i,n;
  double *fatom;

  double local_norm2_sqr = 0.0;
  for (i = 0; i < nvec; i++) local_norm2_sqr += fvec[i]*fvec[i];
  if (nextra_atom) {
    for (int m = 0; m < nextra_atom; m++) {
      fatom = fextra_atom[m];
      n = extra_nlen[m];
      for (i = 0; i < n; i++)
        local_norm2_sqr += fatom[i]*fatom[i];
    }
  }

  double norm2_sqr = 0.0;
  MPI_Allreduce(&local_norm2_sqr,&norm2_sqr,1,MPI_DOUBLE,MPI_SUM,world);

  if (nextra_global)
    for (i = 0; i < nextra_global; i++)
      norm2_sqr += fextra[i]*fextra[i];

  return norm2_sqr;
}
