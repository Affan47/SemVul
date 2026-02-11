RETfar16(bxInstruction_c *i)
{
  Bit16u ip, cs_raw;

  invalidate_prefetch_q();

#if BX_DEBUGGER
  BX_CPU_THIS_PTR show_flag |= Flag_ret;
#endif

  RSP_SPECULATIVE;

  if (protected_mode()) {
    return_protected(i, 0);
    goto done;
  }

  ip     = pop_16();
  cs_raw = pop_16();


  if (ip > BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled) {
    BX_ERROR(("RETfar16: instruction pointer not within code segment limits"));
    exception(BX_GP_EXCEPTION, 0, 0);
  }

  load_seg_reg(&BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS], cs_raw);
  EIP = (Bit32u) ip;

done:
  RSP_COMMIT;

  BX_INSTR_FAR_BRANCH(BX_CPU_ID, BX_INSTR_IS_RET,
                      BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS].selector.value, EIP);
}
