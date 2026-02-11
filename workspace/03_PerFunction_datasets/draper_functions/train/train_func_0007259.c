IRET32(bxInstruction_c *i)
{
  BX_ASSERT(BX_CPU_THIS_PTR cpu_mode != BX_MODE_LONG_64);

  Bit32u eip, eflags32;
  Bit16u cs_raw;

  invalidate_prefetch_q();

#if BX_SUPPORT_VMX
  if (!BX_CPU_THIS_PTR in_vmx_guest || !VMEXIT(VMX_VM_EXEC_CTRL1_NMI_VMEXIT))
#endif
    BX_CPU_THIS_PTR disable_NMI = 0;

#if BX_DEBUGGER
  BX_CPU_THIS_PTR show_flag |= Flag_iret;
#endif

  RSP_SPECULATIVE;

  if (v8086_mode()) {

    iret32_stack_return_from_v86(i);
    goto done;
  }

  if (protected_mode()) {
    iret_protected(i);
    goto done;
  }

  eip      =          pop_32();
  cs_raw   = (Bit16u) pop_32();
  eflags32 =          pop_32();


  if (eip > BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled) {
    BX_ERROR(("IRET32: instruction pointer not within code segment limits"));
    exception(BX_GP_EXCEPTION, 0, 0);
  }

  load_seg_reg(&BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS], cs_raw);
  EIP = eip;
  writeEFlags(eflags32, 0x00257fd5);

done:
  RSP_COMMIT;

  BX_INSTR_FAR_BRANCH(BX_CPU_ID, BX_INSTR_IS_IRET,
                      BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS].selector.value, EIP);
}
