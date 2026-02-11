MemoryMappingChanged(void)
{
  for (unsigned i=0; i<BX_SMP_PROCESSORS; i++)
    BX_CPU(i)->TLB_flush();
}
