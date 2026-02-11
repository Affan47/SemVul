gate_compare_elim_after_reload (void)
{

  if (targetm.flags_regnum == INVALID_REGNUM)
    return false;
  return flag_compare_elim_after_reload;
}
