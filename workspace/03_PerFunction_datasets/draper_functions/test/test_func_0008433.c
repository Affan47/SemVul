cleanup_empty_eh_move_lp (basic_block bb, edge e_out,
			  eh_landing_pad lp, eh_region new_region)
{
  gimple_stmt_iterator gsi;
  eh_landing_pad *pp;

  for (pp = &lp->region->landing_pads; *pp != lp; pp = &(*pp)->next_lp)
    continue;
  *pp = lp->next_lp;

  lp->region = new_region;
  lp->next_lp = new_region->landing_pads;
  new_region->landing_pads = lp;


  gsi = gsi_last_bb (bb);
  mark_virtual_ops_for_renaming (gsi_stmt (gsi));
  gsi_remove (&gsi, true);


  e_out->flags = (e_out->flags & ~EDGE_EH) | EDGE_FALLTHRU;
  e_out->probability = REG_BR_PROB_BASE;
}
