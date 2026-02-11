try_pre_increment_1 (pbi, insn)
     struct propagate_block_info *pbi;
     rtx insn;
{


  rtx x = single_set (insn);
  HOST_WIDE_INT amount = ((GET_CODE (SET_SRC (x)) == PLUS ? 1 : -1)
			  * INTVAL (XEXP (SET_SRC (x), 1)));
  int regno = REGNO (SET_DEST (x));
  rtx y = pbi->reg_next_use[regno];
  if (y != 0
      && SET_DEST (x) != stack_pointer_rtx
      && BLOCK_NUM (y) == BLOCK_NUM (insn)


      && ! dead_or_set_p (y, SET_DEST (x))
      && try_pre_increment (y, SET_DEST (x), amount))
    {


      propagate_block_delete_insn (insn);


      if (regno >= FIRST_PSEUDO_REGISTER)
	{
	  REG_FREQ (regno) += REG_FREQ_FROM_BB (pbi->bb);
	  REG_N_SETS (regno)++;
	}


      invalidate_mems_from_set (pbi, SET_DEST (x));

      return 1;
    }
  return 0;
}
