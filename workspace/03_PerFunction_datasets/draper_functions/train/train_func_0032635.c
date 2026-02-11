get_last_value (const_rtx x)
{
  unsigned int regno;
  rtx value;
  reg_stat_type *rsp;


  if (GET_CODE (x) == SUBREG
      && subreg_lowpart_p (x)
      && !paradoxical_subreg_p (x)
      && (value = get_last_value (SUBREG_REG (x))) != 0)
    return gen_lowpart (GET_MODE (x), value);

  if (!REG_P (x))
    return 0;

  regno = REGNO (x);
  rsp = &reg_stat[regno];
  value = rsp->last_set_value;


  if (value == 0
      || (rsp->last_set_label < label_tick_ebb_start
	  && (regno < FIRST_PSEUDO_REGISTER
	      || REG_N_SETS (regno) != 1
	      || REGNO_REG_SET_P
		 (DF_LR_IN (ENTRY_BLOCK_PTR->next_bb), regno))))
    return 0;


  if (rsp->last_set_label == label_tick
      && DF_INSN_LUID (rsp->last_set) >= subst_low_luid)
    return 0;


  if (get_last_value_validate (&value, rsp->last_set, rsp->last_set_label, 0))
    return value;


  value = copy_rtx (value);
  if (get_last_value_validate (&value, rsp->last_set, rsp->last_set_label, 1))
    return value;

  return 0;
}
