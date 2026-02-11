PSLLQ_PqQq(bxInstruction_c *i)
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

  if(MMXUQ(op2) > 63) {
    MMXUQ(op1) = 0;
  }
  else {
    MMXUQ(op1) <<= MMXUB0(op2);
  }


  BX_WRITE_MMX_REG(i->nnn(), op1);
#else
  BX_INFO(("PSLLQ_PqQq: required MMX, use --enable-mmx option"));
  exception(BX_UD_EXCEPTION, 0, 0);
#endif
}
