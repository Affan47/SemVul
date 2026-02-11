infinite_empty_loop_p (edge e_first)
{
  bool inf_loop = false;
  edge e;

  if (e_first->dest == e_first->src)
    return true;

  e_first->src->aux = (void *) 1;
  for (e = e_first; single_succ_p (e->dest); e = single_succ_edge (e->dest))
    {
      gimple_stmt_iterator gsi;
      if (e->dest->aux)
	{
	  inf_loop = true;
	  break;
	}
      e->dest->aux = (void *) 1;
      gsi = gsi_after_labels (e->dest);
      if (!gsi_end_p (gsi) && is_gimple_debug (gsi_stmt (gsi)))
	gsi_next_nondebug (&gsi);
      if (!gsi_end_p (gsi))
	break;
    }
  e_first->src->aux = NULL;
  for (e = e_first; e->dest->aux; e = single_succ_edge (e->dest))
    e->dest->aux = NULL;

  return inf_loop;
}
