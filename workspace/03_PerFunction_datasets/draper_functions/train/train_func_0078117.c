aarch64_build_constant (int regnum, HOST_WIDE_INT val)
{
  if (aarch64_bitmask_imm (val, DImode))
    emit_move_insn (gen_rtx_REG (Pmode, regnum), GEN_INT (val));
  else
    {
      int i;
      int ncount = 0;
      int zcount = 0;
      HOST_WIDE_INT valp = val >> 16;
      HOST_WIDE_INT valm;
      HOST_WIDE_INT tval;

      for (i = 16; i < 64; i += 16)
	{
	  valm = (valp & 0xffff);

	  if (valm != 0)
	    ++ zcount;

	  if (valm != 0xffff)
	    ++ ncount;

	  valp >>= 16;
	}


      if (ncount < zcount)
	{
	  emit_move_insn (gen_rtx_REG (Pmode, regnum),
			  GEN_INT (val | ~(HOST_WIDE_INT) 0xffff));
	  tval = 0xffff;
	}
      else
	{
	  emit_move_insn (gen_rtx_REG (Pmode, regnum),
			  GEN_INT (val & 0xffff));
	  tval = 0;
	}

      val >>= 16;

      for (i = 16; i < 64; i += 16)
	{
	  if ((val & 0xffff) != tval)
	    emit_insn (gen_insv_immdi (gen_rtx_REG (Pmode, regnum),
				       GEN_INT (i), GEN_INT (val & 0xffff)));
	  val >>= 16;
	}
    }
}
