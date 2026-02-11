handleAlignmentCheck(void)
{
  if (CPL == 3 && BX_CPU_THIS_PTR cr0.get_AM() && BX_CPU_THIS_PTR get_AC()) {
    if (BX_CPU_THIS_PTR alignment_check_mask == 0) {
      BX_CPU_THIS_PTR alignment_check_mask = 0xF;
      BX_INFO(("Enable alignment check (#AC exception)"));
      BX_CPU_THIS_PTR iCache.flushICacheEntries();
    }
  }
  else {
    if (BX_CPU_THIS_PTR alignment_check_mask != 0) {
      BX_CPU_THIS_PTR alignment_check_mask = 0;
      BX_INFO(("Disable alignment check (#AC exception)"));
      BX_CPU_THIS_PTR iCache.flushICacheEntries();
    }
  }
}
