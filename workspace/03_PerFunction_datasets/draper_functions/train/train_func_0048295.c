predlist_merge_sort(struct predlist *list,
		    struct predicate **last)
{
  struct predlist new_list;
  struct predicate *p, *q;

  if (NULL == list->head)
    return;

  if (options.debug_options & DebugTreeOpt)
    {
      fprintf(stderr, "%s:\n", "predlist before merge sort");
      print_tree(stderr, list->head, 2);
    }

  calculate_derived_rates(list->head);
  predlist_init(&new_list);
  while (list->head)
    {

      q = list->head;
      list->head = list->head->pred_left;
      q->pred_left = NULL;


      for (p=new_list.head; p; p=p->pred_left)
	{


	  boolean wantfailure = (OR_PREC != p->p_prec);
	  if (pred_cost_compare(p->pred_right, q->pred_right, wantfailure) >= 0)
	    break;
	}
      if (p)
	{

	  q->pred_left = p->pred_left;
	  if (NULL == q->pred_left)
	    new_list.tail = q;
	  p->pred_left = q;
	}
      else
	{
	  q->pred_left = new_list.head;
	  new_list.head = q;
	  if (NULL == new_list.tail)
	    new_list.tail = q;
	}
    }
  if (options.debug_options & DebugTreeOpt)
    {
      fprintf(stderr, "%s:\n", "predlist after merge sort");
      print_tree(stderr, new_list.head, 2);
    }

  calculate_derived_rates(new_list.head);
  merge_pred(new_list.head, new_list.tail, last);
  predlist_init(list);
}
