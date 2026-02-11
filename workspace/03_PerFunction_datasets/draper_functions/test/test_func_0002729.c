logdet(double const *a, int n)
{


  int N = n*n;
  double *acopy = new double[N];
  for (int i = 0; i < N; i++) {
    acopy[i] = a[i];
  }

  double *w = new double[n];
  int lwork = -1;
  double worktest = 0;
  int info = 0;
  F77_DSYEV("N","U", &n, acopy, &n, w, &worktest, &lwork, &info);
  if (info != 0) {
    delete [] acopy;
    delete [] w;
    throwRuntimeError("unable to calculate workspace size for dsyev");
  }
  lwork = static_cast<int>(worktest);
  double *work = new double[lwork];
  F77_DSYEV("N","U", &n, acopy, &n, w, work, &lwork, &info);
  delete [] acopy;
  delete [] work;
  if (info != 0) {
    delete [] w;
    throwRuntimeError("unable to calculate eigenvalues in dsyev");
  }

  if (w[0] <= 0) {
      throwRuntimeError("Non positive definite matrix in call to logdet");
  }

  double logdet = 0;
  for (int i = 0; i < n; i++) {
    logdet += log(w[i]);
  }
  delete [] w;

  return logdet;
}
