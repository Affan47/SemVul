choose_hard_reg_mode (unsigned int regno ATTRIBUTE_UNUSED,
		      unsigned int nregs, bool call_saved)
{
  unsigned int  m;
  enum machine_mode found_mode = VOIDmode, mode;


  for (mode = GET_CLASS_NARROWEST_MODE (MODE_INT);
       mode != VOIDmode;
       mode = GET_MODE_WIDER_MODE (mode))
    if ((unsigned) hard_regno_nregs[regno][mode] == nregs
	&& HARD_REGNO_MODE_OK (regno, mode)
	&& (! call_saved || ! HARD_REGNO_CALL_PART_CLOBBERED (regno, mode)))
      found_mode = mode;

  if (found_mode != VOIDmode)
    return found_mode;

  for (mode = GET_CLASS_NARROWEST_MODE (MODE_FLOAT);
       mode != VOIDmode;
       mode = GET_MODE_WIDER_MODE (mode))
    if ((unsigned) hard_regno_nregs[regno][mode] == nregs
	&& HARD_REGNO_MODE_OK (regno, mode)
	&& (! call_saved || ! HARD_REGNO_CALL_PART_CLOBBERED (regno, mode)))
      found_mode = mode;

  if (found_mode != VOIDmode)
    return found_mode;

  for (mode = GET_CLASS_NARROWEST_MODE (MODE_VECTOR_FLOAT);
       mode != VOIDmode;
       mode = GET_MODE_WIDER_MODE (mode))
    if ((unsigned) hard_regno_nregs[regno][mode] == nregs
	&& HARD_REGNO_MODE_OK (regno, mode)
	&& (! call_saved || ! HARD_REGNO_CALL_PART_CLOBBERED (regno, mode)))
      found_mode = mode;

  if (found_mode != VOIDmode)
    return found_mode;

  for (mode = GET_CLASS_NARROWEST_MODE (MODE_VECTOR_INT);
       mode != VOIDmode;
       mode = GET_MODE_WIDER_MODE (mode))
    if ((unsigned) hard_regno_nregs[regno][mode] == nregs
	&& HARD_REGNO_MODE_OK (regno, mode)
	&& (! call_saved || ! HARD_REGNO_CALL_PART_CLOBBERED (regno, mode)))
      found_mode = mode;

  if (found_mode != VOIDmode)
    return found_mode;


  for (m = (unsigned int) CCmode; m < (unsigned int) NUM_MACHINE_MODES; ++m)
    {
      mode = (enum machine_mode) m;
      if ((unsigned) hard_regno_nregs[regno][mode] == nregs
	  && HARD_REGNO_MODE_OK (regno, mode)
	  && (! call_saved || ! HARD_REGNO_CALL_PART_CLOBBERED (regno, mode)))
	return mode;
    }


  return VOIDmode;
}
