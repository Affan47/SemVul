FWAIT(bxInstruction_c *i)
{
#if BX_SUPPORT_FPU
  if (BX_CPU_THIS_PTR cr0.get_TS() && BX_CPU_THIS_PTR cr0.get_MP())
    exception(BX_NM_EXCEPTION, 0, 0);

  BX_CPU_THIS_PTR FPU_check_pending_exceptions();
#else
  BX_INFO(("FWAIT: requred FPU, use --enable-fpu"));
#endif
}
