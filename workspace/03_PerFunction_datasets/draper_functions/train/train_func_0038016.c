cpu_loop(Bit32u max_instr_count)
{
#if BX_DEBUGGER
  BX_CPU_THIS_PTR break_point = 0;
  BX_CPU_THIS_PTR magic_break = 0;
  BX_CPU_THIS_PTR stop_reason = STOP_NO_REASON;
#endif

  if (setjmp(BX_CPU_THIS_PTR jmp_buf_env)) {

    BX_INSTR_NEW_INSTRUCTION(BX_CPU_ID);
    BX_TICK1_IF_SINGLE_PROCESSOR();
#if BX_DEBUGGER || BX_GDBSTUB
    if (dbg_instruction_epilog()) return;
#endif
    CHECK_MAX_INSTRUCTIONS(max_instr_count);
#if BX_GDBSTUB
    if (bx_dbg.gdbstub_enabled) return;
#endif
  }


#if BX_DEBUGGER
  if (bx_guard.interrupt_requested) return;
#endif


  BX_CPU_THIS_PTR prev_rip = RIP;
  BX_CPU_THIS_PTR speculative_rsp = 0;
  BX_CPU_THIS_PTR EXT = 0;
  BX_CPU_THIS_PTR errorno = 0;

  while (1) {


    if (BX_CPU_THIS_PTR async_event) {
      if (handleAsyncEvent()) {

        return;
      }
    }

no_async_event:

    bx_address eipBiased = RIP + BX_CPU_THIS_PTR eipPageBias;

    if (eipBiased >= BX_CPU_THIS_PTR eipPageWindowSize) {
      prefetch();
      eipBiased = RIP + BX_CPU_THIS_PTR eipPageBias;
    }

    bx_phy_address pAddr = BX_CPU_THIS_PTR pAddrPage + eipBiased;
    bxICacheEntry_c *entry = BX_CPU_THIS_PTR iCache.get_entry(pAddr, BX_CPU_THIS_PTR fetchModeMask);
    bxInstruction_c *i = entry->i;

    InstrICache_Increment(iCacheLookups);
    InstrICache_Stats();

    if ((entry->pAddr == pAddr) &&
        (entry->writeStamp == *(BX_CPU_THIS_PTR currPageWriteStampPtr)))
    {

    }
    else {


      InstrICache_Increment(iCacheMisses);
      serveICacheMiss(entry, (Bit32u) eipBiased, pAddr);
      i = entry->i;
    }

    BxExecutePtr_tR execute = i->execute;

#if BX_SUPPORT_TRACE_CACHE
    bxInstruction_c *last = i + (entry->ilen);

    for(;;) {
#endif

#if BX_INSTRUMENTATION
      BX_INSTR_OPCODE(BX_CPU_ID, BX_CPU_THIS_PTR eipFetchPtr + (RIP + BX_CPU_THIS_PTR eipPageBias),
         i->ilen(), BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS].cache.u.segment.d_b, Is64BitMode());
#endif

#if BX_DISASM
      if (BX_CPU_THIS_PTR trace) {

        debug_disasm_instruction(BX_CPU_THIS_PTR prev_rip);
      }
#endif


      BX_INSTR_BEFORE_EXECUTION(BX_CPU_ID, i);
      RIP += i->ilen();
      BX_CPU_CALL_METHOD(execute, (i));
      BX_CPU_THIS_PTR prev_rip = RIP;
      BX_INSTR_AFTER_EXECUTION(BX_CPU_ID, i);
      BX_TICK1_IF_SINGLE_PROCESSOR();


      BX_INSTR_NEW_INSTRUCTION(BX_CPU_ID);

#if BX_SUPPORT_TRACE_CACHE
      execute = (++i)->execute;
#endif


#if BX_DEBUGGER || BX_GDBSTUB
      if (dbg_instruction_epilog()) return;
#endif

      CHECK_MAX_INSTRUCTIONS(max_instr_count);

#if BX_SUPPORT_TRACE_CACHE
      if (BX_CPU_THIS_PTR async_event) {

        BX_CPU_THIS_PTR async_event &= ~BX_ASYNC_EVENT_STOP_TRACE;
        break;
      }

      if (i == last) goto no_async_event;
    }
#endif
  }
}
