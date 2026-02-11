simplify_with_current_value_aux (rtx exp)
{
  int i;
  rtx cond;

  switch (GET_CODE (exp))
    {
    case EQ_ATTR:
      if (ATTR_EQ_ATTR_P (exp))
	return false_rtx;
      else
	return true_rtx;
    case CONST_STRING:
    case CONST_INT:
      return exp;

    case IF_THEN_ELSE:
      cond = simplify_with_current_value_aux (XEXP (exp, 0));
      if (cond == true_rtx)
	return simplify_with_current_value_aux (XEXP (exp, 1));
      else if (cond == false_rtx)
	return simplify_with_current_value_aux (XEXP (exp, 2));
      else
	return attr_rtx (IF_THEN_ELSE, cond,
			 simplify_with_current_value_aux (XEXP (exp, 1)),
			 simplify_with_current_value_aux (XEXP (exp, 2)));

    case IOR:
      cond = simplify_with_current_value_aux (XEXP (exp, 1));
      if (cond == true_rtx)
	return cond;
      else if (cond == false_rtx)
	return simplify_with_current_value_aux (XEXP (exp, 0));
      else
	return attr_rtx (IOR, cond,
			 simplify_with_current_value_aux (XEXP (exp, 0)));

    case AND:
      cond = simplify_with_current_value_aux (XEXP (exp, 1));
      if (cond == true_rtx)
	return simplify_with_current_value_aux (XEXP (exp, 0));
      else if (cond == false_rtx)
	return cond;
      else
	return attr_rtx (AND, cond,
			 simplify_with_current_value_aux (XEXP (exp, 0)));

    case NOT:
      cond = simplify_with_current_value_aux (XEXP (exp, 0));
      if (cond == true_rtx)
	return false_rtx;
      else if (cond == false_rtx)
	return true_rtx;
      else
	return attr_rtx (NOT, cond);

    case COND:
      for (i = 0; i < XVECLEN (exp, 0); i += 2)
	{
	  cond = simplify_with_current_value_aux (XVECEXP (exp, 0, i));
	  if (cond == true_rtx)
	    return simplify_with_current_value_aux (XVECEXP (exp, 0, i + 1));
	  else if (cond == false_rtx)
	    continue;
	  else
	    abort ();

	}
      return simplify_with_current_value_aux (XEXP (exp, 1));

    default:
      abort ();
    }
}
