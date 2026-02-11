reg_is_set (reg, setter, data)
     rtx reg;
     rtx setter;
     void *data ATTRIBUTE_UNUSED;
{


  if (GET_CODE (reg) != SUBREG
      && GET_CODE (reg) != REG)
    return;


  reg_is_born (reg, 2 * this_insn_number - (GET_CODE (setter) == CLOBBER));
}
