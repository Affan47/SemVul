cleanup() {
  long i, j;

  for (i = 0; i < NTEMPMATS; i++) {
    for (j = 0; j <= sitelength; j++)
      free(tempmatrix[i][j]);
    free(tempmatrix[i]);
  }
  free(tempmatrix);
  tempmatrix = NULL;
  for (i = 0; i <= sitelength; i++) {
    free(tempslope[i]);
    free(tempcurve[i]);
  }
  free(tempslope);
  tempslope = NULL;
  free(tempcurve);
  tempcurve = NULL;

  freelrsaves();
}
