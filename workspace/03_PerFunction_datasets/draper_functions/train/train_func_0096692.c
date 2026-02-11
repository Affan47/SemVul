set_phases(GtArray *cds_features)
{
  GtPhase phase = GT_PHASE_ZERO;
  GtFeatureNode *cds_feature;
  unsigned long i, length;
  gt_assert(cds_features && gt_array_size(cds_features));
  for (i = 0; i < gt_array_size(cds_features); i++) {
    cds_feature = *(GtFeatureNode**) gt_array_get(cds_features, i);
    gt_feature_node_set_phase(cds_feature, phase);
    length = gt_genome_node_get_length((GtGenomeNode*) cds_feature);
    phase = (3 - (length - phase) % 3) % 3;
    gt_assert(phase <= GT_PHASE_TWO);
  }
}
