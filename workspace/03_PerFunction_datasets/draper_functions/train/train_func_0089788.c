gt_feature_node_has_source(const GtFeatureNode *fn)
{
  gt_assert(fn);
  if (!fn->source || !strcmp(gt_str_get(fn->source), "."))
    return false;
  return true;
}
