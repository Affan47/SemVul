factor_tests (struct decision_head *head)
{
  struct decision *first, *next;

  for (first = head->first; first && first->next; first = next)
    {
      enum decision_type type;
      struct decision *new_dec, *old_last;

      type = first->tests->type;
      next = first->next;


      if (next->tests->type != type)
	continue;


      if (type != DT_mode
	  && type != DT_code
	  && type != DT_veclen
	  && type != DT_elt_zero_int
	  && type != DT_elt_one_int
	  && type != DT_elt_zero_wide_safe)
	continue;


      if (first->tests->next != NULL)
	{
	  new_dec = new_decision (first->position, &first->success);
	  new_dec->tests = first->tests->next;
	  first->tests->next = NULL;
	}


      first->next = NULL;
      old_last = head->last;
      head->last = first;


      do
	{
	  struct decision_head h;

	  if (next->tests->next != NULL)
	    {
	      new_dec = new_decision (next->position, &next->success);
	      new_dec->tests = next->tests->next;
	      next->tests->next = NULL;
	    }
	  new_dec = next;
	  next = next->next;
	  new_dec->next = NULL;
	  h.first = h.last = new_dec;

	  merge_trees (head, &h);
	}
      while (next && next->tests->type == type);


      if (next)
	{
	  next->prev = head->last;
	  head->last->next = next;
	  head->last = old_last;
	}
    }


  for (first = head->first; first; first = first->next)
    factor_tests (&first->success);
}
