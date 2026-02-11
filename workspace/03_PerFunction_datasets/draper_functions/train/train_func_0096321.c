verify_eh_tree (struct function *fun)
{
  eh_region r, outer;
  int nvisited_lp, nvisited_r;
  int count_lp, count_r, depth, i;
  eh_landing_pad lp;
  bool err = false;

  if (!fun->eh->region_tree)
    return;

  count_r = 0;
  for (i = 1; vec_safe_iterate (fun->eh->region_array, i, &r); ++i)
    if (r)
      {
	if (r->index == i)
	  count_r++;
	else
	  {
	    error ("region_array is corrupted for region %i", r->index);
	    err = true;
	  }
      }

  count_lp = 0;
  for (i = 1; vec_safe_iterate (fun->eh->lp_array, i, &lp); ++i)
    if (lp)
      {
	if (lp->index == i)
	  count_lp++;
	else
	  {
	    error ("lp_array is corrupted for lp %i", lp->index);
	    err = true;
	  }
      }

  depth = nvisited_lp = nvisited_r = 0;
  outer = NULL;
  r = fun->eh->region_tree;
  while (1)
    {
      if ((*fun->eh->region_array)[r->index] != r)
	{
	  error ("region_array is corrupted for region %i", r->index);
	  err = true;
	}
      if (r->outer != outer)
	{
	  error ("outer block of region %i is wrong", r->index);
	  err = true;
	}
      if (depth < 0)
	{
	  error ("negative nesting depth of region %i", r->index);
	  err = true;
	}
      nvisited_r++;

      for (lp = r->landing_pads; lp ; lp = lp->next_lp)
	{
	  if ((*fun->eh->lp_array)[lp->index] != lp)
	    {
	      error ("lp_array is corrupted for lp %i", lp->index);
	      err = true;
	    }
	  if (lp->region != r)
	    {
	      error ("region of lp %i is wrong", lp->index);
	      err = true;
	    }
	  nvisited_lp++;
	}

      if (r->inner)
	outer = r, r = r->inner, depth++;
      else if (r->next_peer)
	r = r->next_peer;
      else
	{
	  do
	    {
	      r = r->outer;
	      if (r == NULL)
		goto region_done;
	      depth--;
	      outer = r->outer;
	    }
	  while (r->next_peer == NULL);
	  r = r->next_peer;
	}
    }
 region_done:
  if (depth != 0)
    {
      error ("tree list ends on depth %i", depth);
      err = true;
    }
  if (count_r != nvisited_r)
    {
      error ("region_array does not match region_tree");
      err = true;
    }
  if (count_lp != nvisited_lp)
    {
      error ("lp_array does not match region_tree");
      err = true;
    }

  if (err)
    {
      dump_eh_tree (stderr, fun);
      internal_error ("verify_eh_tree failed");
    }
}
