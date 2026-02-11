df_def_record_1 (df, x, bb, insn)
     struct df *df;
     rtx x;
     basic_block bb;
     rtx insn;
{
  rtx *loc = &SET_DEST (x);
  rtx dst = *loc;
  enum df_ref_flags flags = 0;


  if (GET_CODE (dst) == PARALLEL && GET_MODE (dst) == BLKmode)
    {
      int i;

      for (i = XVECLEN (dst, 0) - 1; i >= 0; i--)
	df_def_record_1 (df, XVECEXP (dst, 0, i), bb, insn);
      return;
    }

#ifdef CLASS_CANNOT_CHANGE_MODE
  if (GET_CODE (dst) == SUBREG
      && CLASS_CANNOT_CHANGE_MODE_P (GET_MODE (SUBREG_REG (dst)),
				     GET_MODE (dst)))
    flags |= DF_REF_MODE_CHANGE;
#endif


  while (GET_CODE (dst) == STRICT_LOW_PART
	 || GET_CODE (dst) == ZERO_EXTRACT
	 || GET_CODE (dst) == SIGN_EXTRACT
	 || read_modify_subreg_p (dst))
    {


      if (GET_CODE (dst) == STRICT_LOW_PART)
	{
	  loc = &XEXP (dst, 0);
	  dst = *loc;
	}
#ifdef CLASS_CANNOT_CHANGE_MODE
      if (GET_CODE (dst) == SUBREG
	  && CLASS_CANNOT_CHANGE_MODE_P (GET_MODE (SUBREG_REG (dst)),
				         GET_MODE (dst)))
        flags |= DF_REF_MODE_CHANGE;
#endif
      loc = &XEXP (dst, 0);
      dst = *loc;
      flags |= DF_REF_READ_WRITE;
    }

  if (GET_CODE (dst) == REG
      || (GET_CODE (dst) == SUBREG && GET_CODE (SUBREG_REG (dst)) == REG))
    df_ref_record (df, dst, loc, insn, DF_REF_REG_DEF, flags);
}
