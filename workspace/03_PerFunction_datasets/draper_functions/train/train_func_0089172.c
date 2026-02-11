splice_viable (struct z_candidate *cands,
	       bool strict_p,
	       bool *any_viable_p)
{
  struct z_candidate *viable;
  struct z_candidate **last_viable;
  struct z_candidate **cand;


  if (processing_template_decl)
    strict_p = true;

  viable = NULL;
  last_viable = &viable;
  *any_viable_p = false;

  cand = &cands;
  while (*cand)
    {
      struct z_candidate *c = *cand;
      if (strict_p ? c->viable == 1 : c->viable)
	{
	  *last_viable = c;
	  *cand = c->next;
	  c->next = NULL;
	  last_viable = &c->next;
	  *any_viable_p = true;
	}
      else
	cand = &c->next;
    }

  return viable ? viable : cands;
}
