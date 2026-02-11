cse_rtx_varies_p (x, from_alias)
     rtx x;
     int from_alias;
{


  if (GET_CODE (x) == REG
      && REGNO_QTY_VALID_P (REGNO (x)))
    {
      int x_q = REG_QTY (REGNO (x));
      struct qty_table_elem *x_ent = &qty_table[x_q];

      if (GET_MODE (x) == x_ent->mode
	  && x_ent->const_rtx != NULL_RTX)
	return 0;
    }

  if (GET_CODE (x) == PLUS
      && GET_CODE (XEXP (x, 1)) == CONST_INT
      && GET_CODE (XEXP (x, 0)) == REG
      && REGNO_QTY_VALID_P (REGNO (XEXP (x, 0))))
    {
      int x0_q = REG_QTY (REGNO (XEXP (x, 0)));
      struct qty_table_elem *x0_ent = &qty_table[x0_q];

      if ((GET_MODE (XEXP (x, 0)) == x0_ent->mode)
	  && x0_ent->const_rtx != NULL_RTX)
	return 0;
    }


  if (GET_CODE (x) == PLUS
      && GET_CODE (XEXP (x, 0)) == REG
      && GET_CODE (XEXP (x, 1)) == REG
      && REGNO_QTY_VALID_P (REGNO (XEXP (x, 0)))
      && REGNO_QTY_VALID_P (REGNO (XEXP (x, 1))))
    {
      int x0_q = REG_QTY (REGNO (XEXP (x, 0)));
      int x1_q = REG_QTY (REGNO (XEXP (x, 1)));
      struct qty_table_elem *x0_ent = &qty_table[x0_q];
      struct qty_table_elem *x1_ent = &qty_table[x1_q];

      if ((GET_MODE (XEXP (x, 0)) == x0_ent->mode)
	  && x0_ent->const_rtx != NULL_RTX
	  && (GET_MODE (XEXP (x, 1)) == x1_ent->mode)
	  && x1_ent->const_rtx != NULL_RTX)
	return 0;
    }

  return rtx_varies_p (x, from_alias);
}
