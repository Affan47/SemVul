extract_true_false_args_from_phi (basic_block dom, gimple phi,
				  tree *true_arg_p, tree *false_arg_p)
{
  basic_block bb = gimple_bb (phi);
  edge true_edge, false_edge, tem;
  tree arg0 = NULL_TREE, arg1 = NULL_TREE;


  extract_true_false_edges_from_block (dom, &true_edge, &false_edge);
  tem = EDGE_PRED (bb, 0);
  if (tem == true_edge
      || (single_pred_p (true_edge->dest)
	  && (tem->src == true_edge->dest
	      || dominated_by_p (CDI_DOMINATORS,
				 tem->src, true_edge->dest))))
    arg0 = PHI_ARG_DEF (phi, tem->dest_idx);
  else if (tem == false_edge
	   || (single_pred_p (false_edge->dest)
	       && (tem->src == false_edge->dest
		   || dominated_by_p (CDI_DOMINATORS,
				      tem->src, false_edge->dest))))
    arg1 = PHI_ARG_DEF (phi, tem->dest_idx);
  else
    return false;
  tem = EDGE_PRED (bb, 1);
  if (tem == true_edge
      || (single_pred_p (true_edge->dest)
	  && (tem->src == true_edge->dest
	      || dominated_by_p (CDI_DOMINATORS,
				 tem->src, true_edge->dest))))
    arg0 = PHI_ARG_DEF (phi, tem->dest_idx);
  else if (tem == false_edge
	   || (single_pred_p (false_edge->dest)
	       && (tem->src == false_edge->dest
		   || dominated_by_p (CDI_DOMINATORS,
				      tem->src, false_edge->dest))))
    arg1 = PHI_ARG_DEF (phi, tem->dest_idx);
  else
    return false;
  if (!arg0 || !arg1)
    return false;

  if (true_arg_p)
    *true_arg_p = arg0;
  if (false_arg_p)
    *false_arg_p = arg1;

  return true;
}
