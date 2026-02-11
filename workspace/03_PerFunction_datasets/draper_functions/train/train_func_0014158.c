gt_feature_node_is_similar(const GtFeatureNode *fn_a,
                                const GtFeatureNode *fn_b)
{
  GtRange range_a, range_b;
  gt_assert(fn_a && fn_b);
  range_a = feature_node_get_range((GtGenomeNode*) fn_a);
  range_b = feature_node_get_range((GtGenomeNode*) fn_b);
  if (!gt_str_cmp(gt_genome_node_get_seqid((GtGenomeNode*) fn_a),
                  gt_genome_node_get_seqid((GtGenomeNode*) fn_b)) &&
      (gt_feature_node_get_type(fn_a) == gt_feature_node_get_type(fn_b)) &&
      (!gt_range_compare(&range_a, &range_b)) &&
      (gt_feature_node_get_strand(fn_a) ==
       gt_feature_node_get_strand(fn_b)) &&
      (gt_feature_node_get_phase(fn_a) ==
       gt_feature_node_get_phase(fn_b))) {
    return true;
  }
  return false;
}
