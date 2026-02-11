gt_feature_node_iterator_new(const GtFeatureNode *fn)
{
  GtFeatureNodeIterator *fni;
  GtFeatureNode *child_feature;
  GtDlistelem *dlistelem;
  gt_assert(fn);
  fni = feature_node_iterator_new_base(fn);
  if (gt_feature_node_is_pseudo((GtFeatureNode*) fn)) {

    for (dlistelem = gt_dlist_last(fn->children); dlistelem != NULL;
         dlistelem = gt_dlistelem_previous(dlistelem)) {
      child_feature = (GtFeatureNode*) gt_dlistelem_get_data(dlistelem);
      gt_array_add(fni->feature_stack, child_feature);
    }
  }
  else
    gt_array_add(fni->feature_stack, fni->fn);
  gt_assert(gt_array_size(fni->feature_stack));
  fni->direct = false;
  return fni;
}
