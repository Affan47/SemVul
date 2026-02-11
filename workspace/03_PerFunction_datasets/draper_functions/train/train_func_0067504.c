reload_combine_note_store (rtx dst, const_rtx set, void *data ATTRIBUTE_UNUSED)
{
  int regno = 0;
  int i;
  enum machine_mode mode = GET_MODE (dst);

  if (GET_CODE (dst) == SUBREG)
    {
      regno = subreg_regno_offset (REGNO (SUBREG_REG (dst)),
				   GET_MODE (SUBREG_REG (dst)),
				   SUBREG_BYTE (dst),
				   GET_MODE (dst));
      dst = SUBREG_REG (dst);
    }


  if (MEM_P (dst))
    {
      dst = XEXP (dst, 0);
      if (GET_CODE (dst) == PRE_INC || GET_CODE (dst) == POST_INC
	  || GET_CODE (dst) == PRE_DEC || GET_CODE (dst) == POST_DEC
	  || GET_CODE (dst) == PRE_MODIFY || GET_CODE (dst) == POST_MODIFY)
	{
	  regno = REGNO (XEXP (dst, 0));
	  mode = GET_MODE (XEXP (dst, 0));
	  for (i = hard_regno_nregs[regno][mode] - 1 + regno; i >= regno; i--)
	    {


	      reg_state[i].use_index = -1;
	      reg_state[i].store_ruid = reload_combine_ruid;
	      reg_state[i].real_store_ruid = reload_combine_ruid;
	    }
	}
      else
        return;
    }

  if (!REG_P (dst))
    return;
  regno += REGNO (dst);


  if (GET_CODE (SET_DEST (set)) == ZERO_EXTRACT
      || GET_CODE (SET_DEST (set)) == STRICT_LOW_PART)
    {
      for (i = hard_regno_nregs[regno][mode] - 1 + regno; i >= regno; i--)
	{
	  reg_state[i].use_index = -1;
	  reg_state[i].store_ruid = reload_combine_ruid;
	  reg_state[i].real_store_ruid = reload_combine_ruid;
	}
    }
  else
    {
      for (i = hard_regno_nregs[regno][mode] - 1 + regno; i >= regno; i--)
	{
	  reg_state[i].store_ruid = reload_combine_ruid;
	  if (GET_CODE (set) == SET)
	    reg_state[i].real_store_ruid = reload_combine_ruid;
	  reg_state[i].use_index = RELOAD_COMBINE_MAX_USES;
	}
    }
}
