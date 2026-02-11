find_last_value (rtx x, rtx *pinsn, rtx valid_to, int allow_hwreg)
{
  rtx p;

  for (p = PREV_INSN (*pinsn); p && !LABEL_P (p);
       p = PREV_INSN (p))
    if (INSN_P (p))
      {
	rtx set = single_set (p);
	rtx note = find_reg_note (p, REG_EQUAL, NULL_RTX);

	if (set && rtx_equal_p (x, SET_DEST (set)))
	  {
	    rtx src = SET_SRC (set);

	    if (note && GET_CODE (XEXP (note, 0)) != EXPR_LIST)
	      src = XEXP (note, 0);

	    if ((valid_to == NULL_RTX
		 || ! modified_between_p (src, PREV_INSN (p), valid_to))


		&& (! (REG_P (src)
		      && REGNO (src) < FIRST_PSEUDO_REGISTER) || allow_hwreg))
	      {
		*pinsn = p;
		return src;
	      }
	  }


	if (reg_set_p (x, p))
	  break;
      }

  return x;
}
