is_predicable (struct queue_elem *elem)
{
  rtvec vec = XVEC (elem->data, 4);
  const char *value;
  int i;

  if (! vec)
    return predicable_default;

  for (i = GET_NUM_ELEM (vec) - 1; i >= 0; --i)
    {
      rtx sub = RTVEC_ELT (vec, i);
      switch (GET_CODE (sub))
	{
	case SET_ATTR:
	  if (strcmp (XSTR (sub, 0), "predicable") == 0)
	    {
	      value = XSTR (sub, 1);
	      goto found;
	    }
	  break;

	case SET_ATTR_ALTERNATIVE:
	  if (strcmp (XSTR (sub, 0), "predicable") == 0)
	    {
	      error_with_line (elem->lineno,
			       "multiple alternatives for `predicable'");
	      return 0;
	    }
	  break;

	case SET:
	  if (GET_CODE (SET_DEST (sub)) != ATTR
	      || strcmp (XSTR (SET_DEST (sub), 0), "predicable") != 0)
	    break;
	  sub = SET_SRC (sub);
	  if (GET_CODE (sub) == CONST_STRING)
	    {
	      value = XSTR (sub, 0);
	      goto found;
	    }


	  error_with_line (elem->lineno,
			   "non-constant value for `predicable'");
	  return 0;

	default:
	  gcc_unreachable ();
	}
    }

  return predicable_default;

 found:


  if (strchr (value, ',') != NULL)
    return 1;
  if (strcmp (value, predicable_true) == 0)
    return 1;
  if (strcmp (value, predicable_false) == 0)
    return 0;

  error_with_line (elem->lineno,
		   "unknown value `%s' for `predicable' attribute", value);
  return 0;
}
