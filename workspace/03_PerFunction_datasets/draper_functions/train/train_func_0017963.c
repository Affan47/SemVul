PUNPCKLWD_PqQd(bxInstruction_c *i)
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

  MMXUW3(result) = MMXUW1(op2);
  MMXUW2(result) = MMXUW1(op1);
  MMXUW1(result) = MMXUW0(op2);
  MMXUW0(result) = MMXUW0(op1);


  BX_WRITE_MMX_REG(i->nnn(), result);
#else
  BX_INFO(("PUNPCKLWD_PqQd: required MMX, use --enable-mmx option"));
  exception(BX_UD_EXCEPTION, 0, 0);
#endif
}
