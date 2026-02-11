PUNPCKLBW_PqQd(bxInstruction_c *i)
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

  MMXUB7(result) = MMXUB3(op2);
  MMXUB6(result) = MMXUB3(op1);
  MMXUB5(result) = MMXUB2(op2);
  MMXUB4(result) = MMXUB2(op1);
  MMXUB3(result) = MMXUB1(op2);
  MMXUB2(result) = MMXUB1(op1);
  MMXUB1(result) = MMXUB0(op2);
  MMXUB0(result) = MMXUB0(op1);


  BX_WRITE_MMX_REG(i->nnn(), result);
#else
  BX_INFO(("PUNPCKLBW_PqQd: required MMX, configure --enable-mmx"));
  exception(BX_UD_EXCEPTION, 0, 0);
#endif
}
