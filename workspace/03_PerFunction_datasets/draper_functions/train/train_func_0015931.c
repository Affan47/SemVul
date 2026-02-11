h8300_hard_regno_rename_ok (unsigned int old_reg ATTRIBUTE_UNUSED,
			    unsigned int new_reg)
{


  if (h8300_current_function_interrupt_function_p ()
      && !regs_ever_live[new_reg])
    return 0;

  return 1;
}
