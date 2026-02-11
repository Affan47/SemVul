dump_igraph_machine (void)
{
  unsigned int i;

  if (!rtl_dump_file || (debug_new_regalloc & DUMP_IGRAPH_M) == 0)
    return;
  ra_debug_msg (DUMP_IGRAPH_M, "g %d %d\n", num_webs - num_subwebs,
	     FIRST_PSEUDO_REGISTER);
  for (i = 0; i < num_webs - num_subwebs; i++)
    {
      struct web *web = ID2WEB (i);
      struct conflict_link *cl;
      int flags = 0;
      int numc = 0;
      int col = 0;
      flags = web->spill_temp & 0xF;
      flags |= ((web->type == PRECOLORED) ? 1 : 0) << 4;
      flags |= (web->add_hardregs & 0xF) << 5;
      for (cl = web->conflict_list; cl; cl = cl->next)
	if (cl->t->id < web->id)
	  numc++;
      ra_debug_msg (DUMP_IGRAPH_M, "n %d %d %d %d %d %d %d\n",
		 web->id, web->color, flags,
		 (unsigned int)web->spill_cost, web->num_defs, web->num_uses,
		 numc);
      if (web->type != PRECOLORED)
	{
	  ra_debug_msg (DUMP_IGRAPH_M, "s %d", web->id);
	  while (1)
	    {
	      unsigned int u = 0;
	      int n;
	      for (n = 0; n < 32 && col < FIRST_PSEUDO_REGISTER; n++, col++)
		if (TEST_HARD_REG_BIT (web->usable_regs, col))
		  u |= 1 << n;
	      ra_debug_msg (DUMP_IGRAPH_M, " %u", u);
	      if (col >= FIRST_PSEUDO_REGISTER)
		break;
	    }
	  ra_debug_msg (DUMP_IGRAPH_M, "\n");
	}
      if (numc)
	{
	  ra_debug_msg (DUMP_IGRAPH_M, "c %d", web->id);
	  for (cl = web->conflict_list; cl; cl = cl->next)
	    {
	      if (cl->t->id < web->id)
		ra_debug_msg (DUMP_IGRAPH_M, " %d", cl->t->id);
	    }
	  ra_debug_msg (DUMP_IGRAPH_M, "\n");
	}
    }
  ra_debug_msg (DUMP_IGRAPH_M, "e\n");
}
