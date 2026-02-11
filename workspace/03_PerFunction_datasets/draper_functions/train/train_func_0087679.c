move_invariants (struct loop *loop)
{
  struct invariant *inv;
  unsigned i;

  FOR_EACH_VEC_ELT (invariant_p, invariants, i, inv)
    move_invariant_reg (loop, i);
  if (flag_ira_loop_pressure && resize_reg_info ())
    {
      FOR_EACH_VEC_ELT (invariant_p, invariants, i, inv)
	if (inv->reg != NULL_RTX)
	  {
	    if (inv->orig_regno >= 0)
	      setup_reg_classes (REGNO (inv->reg),
				 reg_preferred_class (inv->orig_regno),
				 reg_alternate_class (inv->orig_regno),
				 reg_allocno_class (inv->orig_regno));
	    else
	      setup_reg_classes (REGNO (inv->reg),
				 GENERAL_REGS, NO_REGS, GENERAL_REGS);
	  }
    }
}
