make_hard_regno_born (int regno)
{
  unsigned int i;

  lra_assert (regno < FIRST_PSEUDO_REGISTER);
  if (TEST_HARD_REG_BIT (lra_no_alloc_regs, regno)
      || TEST_HARD_REG_BIT (hard_regs_live, regno))
    return;
  SET_HARD_REG_BIT (hard_regs_live, regno);
  sparseset_set_bit (start_living, regno);
  EXECUTE_IF_SET_IN_SPARSESET (pseudos_live, i)
    SET_HARD_REG_BIT (lra_reg_info[i].conflict_hard_regs, regno);
}
