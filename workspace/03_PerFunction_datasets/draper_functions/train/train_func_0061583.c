canonicalize_address (rtx x)
{
  for (;;)
    switch (GET_CODE (x))
      {
      case ASHIFT:
        if (CONST_INT_P (XEXP (x, 1))
            && INTVAL (XEXP (x, 1)) < GET_MODE_BITSIZE (GET_MODE (x))
            && INTVAL (XEXP (x, 1)) >= 0)
	  {
	    HOST_WIDE_INT shift = INTVAL (XEXP (x, 1));
	    PUT_CODE (x, MULT);
	    XEXP (x, 1) = gen_int_mode ((HOST_WIDE_INT) 1 << shift,
					GET_MODE (x));
	  }

	x = XEXP (x, 0);
        break;

      case PLUS:
        if (GET_CODE (XEXP (x, 0)) == PLUS
	    || GET_CODE (XEXP (x, 0)) == ASHIFT
	    || GET_CODE (XEXP (x, 0)) == CONST)
	  canonicalize_address (XEXP (x, 0));

	x = XEXP (x, 1);
        break;

      case CONST:
	x = XEXP (x, 0);
        break;

      default:
        return;
      }
}
