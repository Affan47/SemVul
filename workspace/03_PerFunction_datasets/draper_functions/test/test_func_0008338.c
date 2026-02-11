PACKUSWB_PqQq(bxInstruction_c *i)
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

  MMXUB0(result) = SaturateWordSToByteU(MMXSW0(op1));
  MMXUB1(result) = SaturateWordSToByteU(MMXSW1(op1));
  MMXUB2(result) = SaturateWordSToByteU(MMXSW2(op1));
  MMXUB3(result) = SaturateWordSToByteU(MMXSW3(op1));
  MMXUB4(result) = SaturateWordSToByteU(MMXSW0(op2));
  MMXUB5(result) = SaturateWordSToByteU(MMXSW1(op2));
  MMXUB6(result) = SaturateWordSToByteU(MMXSW2(op2));
  MMXUB7(result) = SaturateWordSToByteU(MMXSW3(op2));


  BX_WRITE_MMX_REG(i->nnn(), result);
#else
  BX_INFO(("PACKUSWB_PqQq: required MMX, use --enable-mmx option"));
  exception(BX_UD_EXCEPTION, 0, 0);
#endif
}
