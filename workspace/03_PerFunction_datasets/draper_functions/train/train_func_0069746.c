noce_try_store_flag (struct noce_if_info *if_info)
{
  int reversep;
  rtx target, seq;

  if (CONST_INT_P (if_info->b)
      && INTVAL (if_info->b) == STORE_FLAG_VALUE
      && if_info->a == const0_rtx)
    reversep = 0;
  else if (if_info->b == const0_rtx
	   && CONST_INT_P (if_info->a)
	   && INTVAL (if_info->a) == STORE_FLAG_VALUE
	   && (reversed_comparison_code (if_info->cond, if_info->jump)
	       != UNKNOWN))
    reversep = 1;
  else
    return FALSE;

  start_sequence ();

  target = noce_emit_store_flag (if_info, if_info->x, reversep, 0);
  if (target)
    {
      if (target != if_info->x)
	noce_emit_move_insn (if_info->x, target);

      seq = end_ifcvt_sequence (if_info);
      if (! seq)
	return FALSE;

      emit_insn_before_setloc (seq, if_info->jump,
			       INSN_LOCATION (if_info->insn_a));
      return TRUE;
    }
  else
    {
      end_sequence ();
      return FALSE;
    }
}
