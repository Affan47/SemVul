randomassign (int nclusters, int nelements, int clusterid[])


{ int i, j;
  int k = 0;
  double p;
  int n = nelements-nclusters;


  for (i = 0; i < nclusters-1; i++)
  { p = 1.0/(nclusters-i);
    j = binomial(n, p);
    n -= j;
    j += k+1;
    for ( ; k < j; k++) clusterid[k] = i;
  }

  for ( ; k < nelements; k++) clusterid[k] = i;


  for (i = 0; i < nelements; i++)
  { j = (int) (i + (nelements-i)*uniform());
    k = clusterid[j];
    clusterid[j] = clusterid[i];
    clusterid[i] = k;
  }

  return;
}
