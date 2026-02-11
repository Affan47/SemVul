loop_delete_branch_edge (edge e, int really_delete)
{
  basic_block src = e->src;
  int irr;
  edge snd;

  if (src->succ->succ_next)
    {
      basic_block newdest;


      if (src->succ->succ_next->succ_next)
	return false;

      if (!any_condjump_p (BB_END (src)))
	return false;

      snd = e == src->succ ? src->succ->succ_next : src->succ;
      newdest = snd->dest;
      if (newdest == EXIT_BLOCK_PTR)
	return false;


      if (!really_delete)
	return true;


      irr = snd->flags & EDGE_IRREDUCIBLE_LOOP;

      if (!redirect_edge_and_branch (e, newdest))
	return false;
      src->succ->flags &= ~EDGE_IRREDUCIBLE_LOOP;
      src->succ->flags |= irr;

      return true;
    }
  else
    {


      abort ();
    }

  return false;
}
