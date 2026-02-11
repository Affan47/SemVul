aarch64_hard_regno_nregs (unsigned regno, enum machine_mode mode)
{
  switch (aarch64_regno_regclass (regno))
    {
    case FP_REGS:
    case FP_LO_REGS:
      return (GET_MODE_SIZE (mode) + UNITS_PER_VREG - 1) / UNITS_PER_VREG;
    default:
      return (GET_MODE_SIZE (mode) + UNITS_PER_WORD - 1) / UNITS_PER_WORD;
    }
  gcc_unreachable ();
}
