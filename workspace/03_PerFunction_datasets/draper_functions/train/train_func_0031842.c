kill_set_value (rtx x, const_rtx set, void *data)
{
  struct value_data *const vd = (struct value_data *) data;
  if (GET_CODE (set) != CLOBBER)
    {
      kill_value (x, vd);
      if (REG_P (x))
	set_value_regno (REGNO (x), GET_MODE (x), vd);
    }
}
