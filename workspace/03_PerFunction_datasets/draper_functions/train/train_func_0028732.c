PUNPCKLDQ_PqQd(bxInstruction_c *i)
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

  MMXUD1(op1) = MMXUD0(op2);


  BX_WRITE_MMX_REG(i->nnn(), op1);
#else
  BX_INFO(("PUNPCKLDQ_PqQd: required MMX, use --enable-mmx option"));
  exception(BX_UD_EXCEPTION, 0, 0);
#endif
}
