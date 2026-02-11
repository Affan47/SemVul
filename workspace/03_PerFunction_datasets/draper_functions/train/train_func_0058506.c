free_for_value_p (int regno, enum machine_mode mode, int opnum,
		  enum reload_type type, rtx value, rtx out, int reloadnum,
		  int ignore_address_reloads)
{
  int nregs = hard_regno_nregs[regno][mode];
  while (nregs-- > 0)
    if (! reload_reg_free_for_value_p (regno, regno + nregs, opnum, type,
				       value, out, reloadnum,
				       ignore_address_reloads))
      return 0;
  return 1;
}
