gimple_predicted_by_p (const_basic_block bb, enum br_predictor predictor)
{
  struct edge_prediction *i;
  void **preds = pointer_map_contains (bb_predictions, bb);

  if (!preds)
    return false;

  for (i = (struct edge_prediction *) *preds; i; i = i->ep_next)
    if (i->ep_predictor == predictor)
      return true;
  return false;
}
