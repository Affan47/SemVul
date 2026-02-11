reg_truncated_to_mode (enum machine_mode mode, const_rtx x)
{
  reg_stat_type *rsp = VEC_index (reg_stat_type, reg_stat, REGNO (x));
  enum machine_mode truncated = rsp->truncated_to_mode;

  if (truncated == 0
      || rsp->truncation_label < label_tick_ebb_start)
    return false;
  if (GET_MODE_SIZE (truncated) <= GET_MODE_SIZE (mode))
    return true;
  if (TRULY_NOOP_TRUNCATION (GET_MODE_BITSIZE (mode),
			     GET_MODE_BITSIZE (truncated)))
    return true;
  return false;
}
