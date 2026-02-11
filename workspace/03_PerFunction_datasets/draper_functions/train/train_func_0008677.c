record_conflict (struct web *web1, struct web *web2)
{
  unsigned int id1 = web1->id, id2 = web2->id;
  unsigned int index = igraph_index (id1, id2);

  if (web1 == web2 || TEST_BIT (igraph, index))
    return;
  if (id1 == id2)
    abort ();


  if ((web1->regno < FIRST_PSEUDO_REGISTER && fixed_regs[web1->regno])
      || (web2->regno < FIRST_PSEUDO_REGISTER && fixed_regs[web2->regno]))
    return;


  if ((web1->type == PRECOLORED
       && ! TEST_HARD_REG_BIT (web2->usable_regs, web1->regno))
      || (web2->type == PRECOLORED
	  && ! TEST_HARD_REG_BIT (web1->usable_regs, web2->regno)))
    return;


  if (web1->type != PRECOLORED && web2->type != PRECOLORED
      && ! hard_regs_intersect_p (&web1->usable_regs, &web2->usable_regs))
    {
      struct web *p1 = find_web_for_subweb (web1);
      struct web *p2 = find_web_for_subweb (web2);


      bitmap_set_bit (p1->useless_conflicts, p2->id);
      bitmap_set_bit (p2->useless_conflicts, p1->id);
      return;
    }
  SET_BIT (igraph, index);
  add_conflict_edge (web1, web2);
  add_conflict_edge (web2, web1);
}
