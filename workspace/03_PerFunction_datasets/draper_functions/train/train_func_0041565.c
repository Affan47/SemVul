is_subseq (conversion *ics1, conversion *ics2)
{


  while (ics1->kind == ck_rvalue
	 || ics1->kind == ck_lvalue)
    ics1 = ics1->u.next;

  while (1)
    {
      while (ics2->kind == ck_rvalue
	     || ics2->kind == ck_lvalue)
	ics2 = ics2->u.next;

      if (ics2->kind == ck_user
	  || ics2->kind == ck_ambig
	  || ics2->kind == ck_aggr
	  || ics2->kind == ck_list
	  || ics2->kind == ck_identity)


	return false;

      ics2 = ics2->u.next;

      if (ics2->kind == ics1->kind
	  && same_type_p (ics2->type, ics1->type)
	  && same_type_p (ics2->u.next->type,
			  ics1->u.next->type))
	return true;
    }
}
