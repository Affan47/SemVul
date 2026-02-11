ppc32_mem_shutdown(cpu_ppc_t *cpu)
{
   if (cpu != NULL) {

      free(cpu->mts_cache[PPC32_MTS_ICACHE]);
      free(cpu->mts_cache[PPC32_MTS_DCACHE]);
      cpu->mts_cache[PPC32_MTS_ICACHE] = NULL;
      cpu->mts_cache[PPC32_MTS_DCACHE] = NULL;
   }
}
