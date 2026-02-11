filter_intrinsic(int nts, const int *fmasc, double *array1, double *array2)
{
  int i;

  fft2(array1, array2, nts, 1);
  for ( i = 0; i < nts; i++ )
    if ( ! fmasc[i] )  array1[i] = array2[i] = 0;
  fft2(array1, array2, nts, -1);

  return;
}
