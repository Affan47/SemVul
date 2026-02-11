merge_lists(int *nl, const double *restrict l1, const double *restrict l2, long *idx)
{


  const int n1=nl[0], n2=nl[1];
  int i1=0, i2=0, i=0, ii=0;

  while ( i2 < n2 && i1 < n1 )
    {
      if ( l1[i1] < l2[i2] )
	{ idx[i] = i1;    i1++; i++; }
      else
	{ idx[i] = n1+i2; i2++; i++; }
    }

  for ( ii=i1; i1 < n1; ii++ ) {idx[i] = i1;    i++; i1++; }
  for ( ii=i2; i2 < n2; ii++ ) {idx[i] = n1+i2; i++; i2++; }

  return;
}
