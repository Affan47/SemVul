use_related_value (rtx x, struct table_elt *elt)
{
  struct table_elt *relt = 0;
  struct table_elt *p, *q;
  HOST_WIDE_INT offset;


  if (elt != 0 && elt->related_value != 0)
    relt = elt;
  else if (elt == 0 && GET_CODE (x) == CONST)
    {
      rtx subexp = get_related_value (x);
      if (subexp != 0)
	relt = lookup (subexp,
		       safe_hash (subexp, GET_MODE (subexp)) & HASH_MASK,
		       GET_MODE (subexp));
    }

  if (relt == 0)
    return 0;


  p = relt;
  while (1)
    {


      if (rtx_equal_p (x, p->exp))
	q = 0;
      else
	for (q = p->first_same_value; q; q = q->next_same_value)
	  if (GET_CODE (q->exp) == REG)
	    break;

      if (q)
	break;

      p = p->related_value;


      if (p == relt || p == 0)
	break;
    }

  if (q == 0)
    return 0;

  offset = (get_integer_term (x) - get_integer_term (p->exp));

  return plus_constant (q->exp, offset);
}
