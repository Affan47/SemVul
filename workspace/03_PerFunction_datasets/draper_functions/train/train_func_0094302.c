clear_bb_predictions (basic_block bb)
{
  void **preds = pointer_map_contains (bb_predictions, bb);
  struct edge_prediction *pred, *next;

  if (!preds)
    return;

  for (pred = (struct edge_prediction *) *preds; pred; pred = next)
    {
      next = pred->ep_next;
      free (pred);
    }
  *preds = NULL;
}
