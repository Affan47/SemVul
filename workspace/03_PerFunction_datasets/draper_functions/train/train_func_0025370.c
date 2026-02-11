gt_feature_node_get_phase(const GtFeatureNode *fn)
{
  gt_assert(fn);
  return (fn->bit_field >> PHASE_OFFSET) & PHASE_MASK;
}
