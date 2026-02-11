GetCoarseEquivalent(
    const JSObjectsCluster& cluster) {
  if (!cluster.can_be_coarsed()) return JSObjectsCluster();
  EqualityTree::Locator loc;
  return eq_tree_.Find(cluster, &loc) ? loc.value() : JSObjectsCluster();
}
