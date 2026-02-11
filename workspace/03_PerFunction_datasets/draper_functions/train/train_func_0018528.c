grsc(X,d)
double *X;
INT d;
{ INT i, j, k;
  double nx;
  for (i=0; i<d; i++)
  { nx = 0;
    for (j=0; j<d; j++) nx += X[i*d+j]*X[i*d+j];
    nx = sqrt(nx);
    for (j=0; j<d; j++) X[i*d+j] /= nx;
    for (j=i+1; j<d; j++)
    { nx = 0;
      for (k=0; k<d; k++) nx += X[i*d+k]*X[j*d+k];
      for (k=0; k<d; k++) X[j*d+k] -= nx*X[i*d+k];
    }
  }
}
