Call(const JSObjectsCluster& cluster,
                           JSObjectsClusterTree* tree) {
  if (!cluster.can_be_coarsed()) return;
  ClusterBackRefs pair(cluster);
  ASSERT(current_pair_ == NULL);
  current_pair_ = &pair;
  current_set_ = new JSObjectsRetainerTree();
  self_ = &cluster;
  tree->ForEach(this);
  sim_list_.Add(pair);
  current_pair_ = NULL;
  current_set_ = NULL;
  self_ = NULL;
}
