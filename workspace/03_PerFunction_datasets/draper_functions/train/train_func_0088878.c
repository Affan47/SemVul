prepareFPU(bxInstruction_c *i, bx_bool check_pending_exceptions)
{
  if (BX_CPU_THIS_PTR cr0.get_EM() || BX_CPU_THIS_PTR cr0.get_TS())
    exception(BX_NM_EXCEPTION, 0, 0);

  if (check_pending_exceptions)
    BX_CPU_THIS_PTR FPU_check_pending_exceptions();
}
