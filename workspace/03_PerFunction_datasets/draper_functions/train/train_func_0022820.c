branch_near32(Bit32u new_EIP)
{
  BX_ASSERT(BX_CPU_THIS_PTR cpu_mode != BX_MODE_LONG_64);


  if (new_EIP > BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled)
  {
    BX_ERROR(("branch_near32: offset outside of CS limits"));
    exception(BX_GP_EXCEPTION, 0, 0);
  }

  EIP = new_EIP;

#if BX_SUPPORT_TRACE_CACHE && !defined(BX_TRACE_CACHE_NO_SPECULATIVE_TRACING)

  BX_CPU_THIS_PTR async_event |= BX_ASYNC_EVENT_STOP_TRACE;
#endif
}
