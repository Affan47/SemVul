add_auto_sr_to_queue(GT_UNUSED void *key, void *value, void *data,
                                GT_UNUSED GtError *err)
{
  AutomaticSequenceRegion *auto_sr = value;
  GtQueue *genome_nodes = data;
  GtGenomeNode *gf;
  unsigned int i;
  gt_error_check(err);
  gt_assert(key && value && data);
  if (gt_array_size(auto_sr->feature_nodes)) {
    gt_queue_add(genome_nodes, auto_sr->sequence_region);
    auto_sr->sequence_region = NULL;
    for (i = 0; i < gt_array_size(auto_sr->feature_nodes); i++) {
      gf = *(GtGenomeNode**) gt_array_get(auto_sr->feature_nodes, i);
      gt_queue_add(genome_nodes, gf);
    }
    gt_array_reset(auto_sr->feature_nodes);
  }
  return 0;
}
