validateCluster (int n, int* grouping, int clust_num)
{
  int i;
  for (i = 0; i < n; i++) {
      if (grouping[i] == clust_num) return clust_num;
  }
  fprintf (stderr, "Highlighted cluster %d not found - ignored\n", clust_num);
  return 0;
}
