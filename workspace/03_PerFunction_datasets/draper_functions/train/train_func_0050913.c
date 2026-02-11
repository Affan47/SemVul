PADDSB_PqQq(bxInstruction_c *i)
{
#if BX_SUPPORT_MMX
  BX_CPU_THIS_PTR prepareMMX();

  BxPackedMmxRegister op1 = BX_READ_MMX_REG(i->nnn()), op2, result;


  if (i->modC0()) {
    op2 = BX_READ_MMX_REG(i->rm());
  }
  else {
    bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

    MMXUQ(op2) = read_virtual_qword(i->seg(), eaddr);
  }

  BX_CPU_THIS_PTR prepareFPU2MMX();

  MMXSB0(result) = SaturateWordSToByteS(Bit16s(MMXSB0(op1)) + Bit16s(MMXSB0(op2)));
  MMXSB1(result) = SaturateWordSToByteS(Bit16s(MMXSB1(op1)) + Bit16s(MMXSB1(op2)));
  MMXSB2(result) = SaturateWordSToByteS(Bit16s(MMXSB2(op1)) + Bit16s(MMXSB2(op2)));
  MMXSB3(result) = SaturateWordSToByteS(Bit16s(MMXSB3(op1)) + Bit16s(MMXSB3(op2)));
  MMXSB4(result) = SaturateWordSToByteS(Bit16s(MMXSB4(op1)) + Bit16s(MMXSB4(op2)));
  MMXSB5(result) = SaturateWordSToByteS(Bit16s(MMXSB5(op1)) + Bit16s(MMXSB5(op2)));
  MMXSB6(result) = SaturateWordSToByteS(Bit16s(MMXSB6(op1)) + Bit16s(MMXSB6(op2)));
  MMXSB7(result) = SaturateWordSToByteS(Bit16s(MMXSB7(op1)) + Bit16s(MMXSB7(op2)));


  BX_WRITE_MMX_REG(i->nnn(), result);
#else
  BX_INFO(("PADDSB_PqQq: required MMX, use --enable-mmx option"));
  exception(BX_UD_EXCEPTION, 0, 0);
#endif
}
