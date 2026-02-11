FTST(bxInstruction_c *i)
{
#if BX_SUPPORT_FPU
  BX_CPU_THIS_PTR prepareFPU(i);
  BX_CPU_THIS_PTR FPU_update_last_instruction(i);

  clear_C1();

  if (IS_TAG_EMPTY(0)) {
     FPU_exception(FPU_EX_Stack_Underflow);
     setcc(FPU_SW_C0|FPU_SW_C2|FPU_SW_C3);
  }
  else {
     extern const floatx80 Const_Z;

     float_status_t status =
        FPU_pre_exception_handling(BX_CPU_THIS_PTR the_i387.get_control_word());

     int rc = floatx80_compare(BX_READ_FPU_REG(0), Const_Z, status);
     setcc(status_word_flags_fpu_compare(rc));
     FPU_exception(status.float_exception_flags);
  }
#else
  BX_INFO(("FTST: required FPU, configure --enable-fpu"));
#endif
}
