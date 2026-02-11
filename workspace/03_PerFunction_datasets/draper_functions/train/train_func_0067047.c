reg_fits_class_p (const_rtx operand, reg_class_t cl, int offset,
		  enum machine_mode mode)
{
  unsigned int regno = REGNO (operand);

  if (cl == NO_REGS)
    return false;


  return (HARD_REGISTER_NUM_P (regno)
	  && HARD_REGISTER_NUM_P (regno + offset)
	  && in_hard_reg_set_p (reg_class_contents[(int) cl], mode,
				regno + offset));
}
