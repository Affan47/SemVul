substitute_address (exp, no_address_fn, address_fn)
     rtx exp;
     rtx (*no_address_fn) PARAMS ((rtx));
     rtx (*address_fn) PARAMS ((rtx));
{
  int i;
  rtx newexp;

  if (GET_CODE (exp) == COND)
    {

      address_used = 0;
      for (i = 0; i < XVECLEN (exp, 0); i += 2)
	walk_attr_value (XVECEXP (exp, 0, i));

      if (address_used)
	return (*address_fn) (exp);


      newexp = rtx_alloc (COND);
      XVEC (newexp, 0) = rtvec_alloc (XVECLEN (exp, 0));
      for (i = 0; i < XVECLEN (exp, 0); i += 2)
	{
	  XVECEXP (newexp, 0, i) = XVECEXP (exp, 0, i);
	  XVECEXP (newexp, 0, i + 1)
	    = substitute_address (XVECEXP (exp, 0, i + 1),
				  no_address_fn, address_fn);
	}

      XEXP (newexp, 1) = substitute_address (XEXP (exp, 1),
					     no_address_fn, address_fn);

      return newexp;
    }

  else if (GET_CODE (exp) == IF_THEN_ELSE)
    {
      address_used = 0;
      walk_attr_value (XEXP (exp, 0));
      if (address_used)
	return (*address_fn) (exp);

      return attr_rtx (IF_THEN_ELSE,
		       substitute_address (XEXP (exp, 0),
					   no_address_fn, address_fn),
		       substitute_address (XEXP (exp, 1),
					   no_address_fn, address_fn),
		       substitute_address (XEXP (exp, 2),
					   no_address_fn, address_fn));
    }

  return (*no_address_fn) (exp);
}
