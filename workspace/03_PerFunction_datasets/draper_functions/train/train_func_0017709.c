CMPXCHG_EdGdR(bxInstruction_c *i)
{
#if BX_CPU_LEVEL >= 4
  Bit32u op1_32, op2_32, diff_32;

  op1_32 = BX_READ_32BIT_REG(i->rm());
  diff_32 = EAX - op1_32;
  SET_FLAGS_OSZAPC_SUB_32(EAX, op1_32, diff_32);

  if (diff_32 == 0) {

    op2_32 = BX_READ_32BIT_REG(i->nnn());
    BX_WRITE_32BIT_REGZ(i->rm(), op2_32);
  }
  else {

    RAX = op1_32;
  }
#else
  BX_INFO(("CMPXCHG_EdGd: not supported for cpulevel <= 3"));
  exception(BX_UD_EXCEPTION, 0, 0);
#endif
}
