PADDB_PqQq(bxInstruction_c *i)
{
#if BX_SUPPORT_MMX
  BX_CPU_THIS_PTR prepareMMX();

  BxPackedMmxRegister op1 = BX_READ_MMX_REG(i->nnn()), op2;


  if (i->modC0()) {
    op2 = BX_READ_MMX_REG(i->rm());
  }
  else {
    bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

    MMXUQ(op2) = read_virtual_qword(i->seg(), eaddr);
  }

  BX_CPU_THIS_PTR prepareFPU2MMX();

  MMXUB0(op1) += MMXUB0(op2);
  MMXUB1(op1) += MMXUB1(op2);
  MMXUB2(op1) += MMXUB2(op2);
  MMXUB3(op1) += MMXUB3(op2);
  MMXUB4(op1) += MMXUB4(op2);
  MMXUB5(op1) += MMXUB5(op2);
  MMXUB6(op1) += MMXUB6(op2);
  MMXUB7(op1) += MMXUB7(op2);


  BX_WRITE_MMX_REG(i->nnn(), op1);
#else
  BX_INFO(("PADDB_PqQq: required MMX, use --enable-mmx option"));
  exception(BX_UD_EXCEPTION, 0, 0);
#endif
}
