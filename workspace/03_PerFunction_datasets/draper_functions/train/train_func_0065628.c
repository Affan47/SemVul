FPREM(bxInstruction_c *i)
{
#if BX_SUPPORT_FPU
  BX_CPU_THIS_PTR prepareFPU(i);
  BX_CPU_THIS_PTR FPU_update_last_instruction(i);

  clear_C1();
  clear_C2();

  if (IS_TAG_EMPTY(0) || IS_TAG_EMPTY(1))
  {
     FPU_stack_underflow(0);
     return;
  }

  float_status_t status =
     FPU_pre_exception_handling(BX_CPU_THIS_PTR the_i387.get_control_word());

  Bit64u quotient;

  floatx80 a = BX_READ_FPU_REG(0);
  floatx80 b = BX_READ_FPU_REG(1);

  floatx80 result = floatx80_remainder(a, b, quotient, status);

  if (! FPU_exception(status.float_exception_flags)) {
     int cc = 0;
     if (quotient == (Bit64u) -1) cc = FPU_SW_C2;
     else {
        if (quotient & 1) cc |= FPU_SW_C1;
        if (quotient & 2) cc |= FPU_SW_C3;
        if (quotient & 4) cc |= FPU_SW_C0;
     }
     setcc(cc);

     BX_WRITE_FPU_REG(result, 0);
  }
#else
  BX_INFO(("FPREM: required FPU, configure --enable-fpu"));
#endif
}
