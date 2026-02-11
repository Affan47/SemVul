qh_memsetup (void) {
  int k,i;

  qsort(qhmem.sizetable, qhmem.TABLEsize, sizeof(int), qh_intcompare);
  qhmem.LASTsize= qhmem.sizetable[qhmem.TABLEsize-1];

  if (qhmem .LASTsize >= qhmem .BUFsize || qhmem.LASTsize >= qhmem .BUFinit)
    qhull_fatal(7);

  if (!(qhmem.indextable= (int *)malloc((qhmem.LASTsize+1) * sizeof(int))))
    qhull_fatal(8);

  for(k=qhmem.LASTsize+1; k--; )
    qhmem.indextable[k]= k;
  i= 0;
  for(k= 0; k <= qhmem.LASTsize; k++) {
    if (qhmem.indextable[k] <= qhmem.sizetable[i])
      qhmem.indextable[k]= i;
    else
      qhmem.indextable[k]= ++i;
  }
}
