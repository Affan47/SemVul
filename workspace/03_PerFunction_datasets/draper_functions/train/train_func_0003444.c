sa_clusters_free(GtArray *saclusters)
{
  GthSACluster *sacluster;
  unsigned long i;
  for (i = 0; i < gt_array_size(saclusters); i++) {
    sacluster = *(GthSACluster**) gt_array_get(saclusters, i);
    gt_array_delete(sacluster->members);
    gt_free(sacluster);
  }
  gt_array_delete(saclusters);
}
