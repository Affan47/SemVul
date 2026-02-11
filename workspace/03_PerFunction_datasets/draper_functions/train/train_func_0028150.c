deps_may_trap_p (const_rtx mem)
{
  const_rtx addr = XEXP (mem, 0);

  if (REG_P (addr) && REGNO (addr) >= FIRST_PSEUDO_REGISTER)
    {
      const_rtx t = get_reg_known_value (REGNO (addr));
      if (t)
	addr = t;
    }
  return rtx_addr_can_trap_p (addr);
}
