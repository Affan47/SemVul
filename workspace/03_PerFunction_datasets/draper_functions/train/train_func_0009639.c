clobbers_queued_reg_save (const_rtx insn)
{
  struct queued_reg_save *q;

  for (q = queued_reg_saves; q; q = q->next)
    {
      size_t i;
      if (modified_in_p (q->reg, insn))
	return true;
      for (i = 0; i < num_regs_saved_in_regs; i++)
	if (REGNO (q->reg) == REGNO (regs_saved_in_regs[i].orig_reg)
	    && modified_in_p (regs_saved_in_regs[i].saved_in_reg, insn))
	  return true;
    }

  return false;
}
