solvetrid(X,y,m)
double *X, *y;
INT m;
{ INT i;
  double s;
  for (i=1; i<m; i++)
  { s = X[3*i]/X[3*i-2];
    X[3*i] = 0; X[3*i+1] -= s*X[3*i-1];
    y[i] -= s*y[i-1];
  }
  for (i=m-2; i>=0; i--)
  { s = X[3*i+2]/X[3*i+4];
    X[3*i+2] = 0;
    y[i] -= s*y[i+1];
  }
  for (i=0; i<m; i++) y[i] /= X[3*i+1];
}
