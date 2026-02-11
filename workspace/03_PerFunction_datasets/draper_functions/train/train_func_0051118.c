gt_feature_node_number_of_children_of_type(const GtFeatureNode
                                                         *parent,
                                                         const GtFeatureNode
                                                         *node)
{
  GT_UNUSED int had_err = 0;
  GtTypeTraverseInfo traverseinfo;
  gt_assert(parent && node);
  traverseinfo.type = gt_feature_node_get_type(node);
  traverseinfo.number = 0;
  had_err = gt_feature_node_traverse_direct_children((GtFeatureNode*) parent,
                                                     &traverseinfo, count_types,
                                                     NULL);
  return traverseinfo.number;
}
