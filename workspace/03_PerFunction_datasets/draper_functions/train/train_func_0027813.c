init_v8086_mode(void)
{
  for(unsigned sreg = 0; sreg < 6; sreg++) {
    BX_CPU_THIS_PTR sregs[sreg].cache.valid   = SegValidCache | SegAccessROK | SegAccessWOK;
    BX_CPU_THIS_PTR sregs[sreg].cache.p       = 1;
    BX_CPU_THIS_PTR sregs[sreg].cache.dpl     = 3;
    BX_CPU_THIS_PTR sregs[sreg].cache.segment = 1;
    BX_CPU_THIS_PTR sregs[sreg].cache.type    = BX_DATA_READ_WRITE_ACCESSED;

    BX_CPU_THIS_PTR sregs[sreg].cache.u.segment.base =
        BX_CPU_THIS_PTR sregs[sreg].selector.value << 4;
    BX_CPU_THIS_PTR sregs[sreg].cache.u.segment.limit_scaled = 0xffff;
    BX_CPU_THIS_PTR sregs[sreg].cache.u.segment.g            = 0;
    BX_CPU_THIS_PTR sregs[sreg].cache.u.segment.d_b          = 0;
    BX_CPU_THIS_PTR sregs[sreg].cache.u.segment.avl          = 0;
    BX_CPU_THIS_PTR sregs[sreg].selector.rpl                 = 3;
  }

  handleCpuModeChange();

#if BX_CPU_LEVEL >= 4 && BX_SUPPORT_ALIGNMENT_CHECK
  handleAlignmentCheck();
#endif
}
