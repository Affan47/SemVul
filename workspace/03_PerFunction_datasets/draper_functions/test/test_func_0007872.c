mark_pseudo_dead (int regno, int point)
{
  lra_live_range_t p;

  lra_assert (regno >= FIRST_PSEUDO_REGISTER);
  lra_assert (sparseset_bit_p (pseudos_live, regno));
  sparseset_clear_bit (pseudos_live, regno);
  sparseset_set_bit (start_dying, regno);
  if (complete_info_p || lra_get_regno_hard_regno (regno) < 0)
    {
      p = lra_reg_info[regno].live_ranges;
      lra_assert (p != NULL);
      p->finish = point;
    }
}
