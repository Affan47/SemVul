FST_SINGLE_REAL(bxInstruction_c *i)
{
#if BX_SUPPORT_FPU
  BX_CPU_THIS_PTR prepareFPU(i);

  RMAddr(i) = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  FPU_update_last_instruction(i);

  Bit16u x87_sw = FPU_PARTIAL_STATUS;

  clear_C1();

  float32 save_reg = float32_default_nan;

  int pop_stack = i->nnn() & 1;

  if (IS_TAG_EMPTY(0))
  {
     FPU_exception(FPU_EX_Stack_Underflow);

     if (! BX_CPU_THIS_PTR the_i387.is_IA_masked())
        return;
  }
  else
  {
     float_status_t status =
         FPU_pre_exception_handling(BX_CPU_THIS_PTR the_i387.get_control_word());

     save_reg = floatx80_to_float32(BX_READ_FPU_REG(0), status);

     if (FPU_exception(status.float_exception_flags, 1))
        return;
  }


  swap_values(x87_sw, FPU_PARTIAL_STATUS);

  write_virtual_dword(i->seg(), RMAddr(i), save_reg);

  FPU_PARTIAL_STATUS = x87_sw;
  if (pop_stack)
     BX_CPU_THIS_PTR the_i387.FPU_pop();
#else
  BX_INFO(("FST(P)_SINGLE_REAL: required FPU, configure --enable-fpu"));
#endif
}
