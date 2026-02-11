mark_reg_pointer (reg, align)
     rtx reg;
     int align;
{
  if (! REG_POINTER (reg))
    {
      REG_POINTER (reg) = 1;

      if (align)
	REGNO_POINTER_ALIGN (REGNO (reg)) = align;
    }
  else if (align && align < REGNO_POINTER_ALIGN (REGNO (reg)))

    REGNO_POINTER_ALIGN (REGNO (reg)) = align;
}
