feature_node_is_part_of_pseudo_node(GtFeatureNode *pseudo_node,
                                                GtFeatureNode *child,
                                                GtFeatureInfo *feature_info)
{
  const char *id;
  gt_assert(pseudo_node &&
            gt_feature_node_is_pseudo((GtFeatureNode*) pseudo_node));
  gt_assert(child && !gt_feature_node_is_pseudo((GtFeatureNode*) child));
  gt_assert(feature_info);
  gt_feature_node_add_child(pseudo_node, child);
  id = gt_feature_node_get_attribute(child, GT_GFF_ID);
  gt_assert(id);
  gt_feature_info_add_pseudo_parent(feature_info, id, pseudo_node);
}
