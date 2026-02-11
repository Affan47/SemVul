collect_one_action_chain (htab_t ar_hash, eh_region region)
{
  int next;


  if (region == NULL)
    return -1;

  switch (region->type)
    {
    case ERT_CLEANUP:
      {
	eh_region r;


	next = collect_one_action_chain (ar_hash, region->outer);
	if (next <= 0)
	  return 0;
	for (r = region->outer; r ; r = r->outer)
	  if (r->type == ERT_CLEANUP)
	    return next;
	return add_action_record (ar_hash, 0, next);
      }

    case ERT_TRY:
      {
	eh_catch c;


	next = -3;
	for (c = region->u.eh_try.last_catch; c ; c = c->prev_catch)
	  {
	    if (c->type_list == NULL)
	      {


		int filter = TREE_INT_CST_LOW (TREE_VALUE (c->filter_list));
		next = add_action_record (ar_hash, filter, 0);
	      }
	    else
	      {


		tree flt_node;

		if (next == -3)
		  {
		    next = collect_one_action_chain (ar_hash, region->outer);


		    if (next == -1)
		      next = 0;


		    else if (next <= 0)
		      next = add_action_record (ar_hash, 0, 0);
		  }

		flt_node = c->filter_list;
		for (; flt_node; flt_node = TREE_CHAIN (flt_node))
		  {
		    int filter = TREE_INT_CST_LOW (TREE_VALUE (flt_node));
		    next = add_action_record (ar_hash, filter, next);
		  }
	      }
	  }
	return next;
      }

    case ERT_ALLOWED_EXCEPTIONS:


      next = collect_one_action_chain (ar_hash, region->outer);


      if (next == -1)
	next = 0;


      else if (next <= 0)
	next = add_action_record (ar_hash, 0, 0);

      return add_action_record (ar_hash, region->u.allowed.filter, next);

    case ERT_MUST_NOT_THROW:


      return -2;
    }

  gcc_unreachable ();
}
