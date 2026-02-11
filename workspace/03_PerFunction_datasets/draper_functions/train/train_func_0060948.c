FSTP_EXTENDED_REAL(bxInstruction_c *i)
{
#if BX_SUPPORT_FPU
  BX_CPU_THIS_PTR prepareFPU(i);

  RMAddr(i) = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  FPU_update_last_instruction(i);

  clear_C1();

  floatx80 save_reg = floatx80_default_nan;

  if (IS_TAG_EMPTY(0))
  {
     FPU_exception(FPU_EX_Stack_Underflow);

     if (! BX_CPU_THIS_PTR the_i387.is_IA_masked())
        return;
  }
  else
  {
     save_reg = BX_READ_FPU_REG(0);
  }

  write_virtual_qword(i->seg(), RMAddr(i),     save_reg.fraction);
  write_virtual_word (i->seg(), RMAddr(i) + 8, save_reg.exp);

  BX_CPU_THIS_PTR the_i387.FPU_pop();
#else
  BX_INFO(("FSTP_EXTENDED_REAL: required FPU, configure --enable-fpu"));
#endif
}
