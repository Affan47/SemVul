mips64_cp0_exec_tlbp(cpu_mips_t *cpu)
{
   mips_cp0_t *cp0 = &cpu->cp0;
   m_uint64_t hi_reg,asid;
   m_uint64_t vpn2,vpn2_mask;
   tlb_entry_t *entry;
   int i;

   vpn2_mask = mips64_cp0_get_vpn2_mask(cpu);
   hi_reg = cp0->reg[MIPS_CP0_TLB_HI];
   asid = hi_reg & MIPS_TLB_ASID_MASK;
   vpn2 = hi_reg & vpn2_mask;

   cp0->reg[MIPS_CP0_INDEX] = 0xffffffff80000000ULL;

   for(i=0;i<cp0->tlb_entries;i++) {
      entry = &cp0->tlb[i];

      if (((entry->hi & vpn2_mask) == vpn2) &&
          ((entry->hi & MIPS_TLB_G_MASK) ||
           ((entry->hi & MIPS_TLB_ASID_MASK) == asid)))
      {
         cp0->reg[MIPS_CP0_INDEX] = i;
#if DEBUG_TLB_ACTIVITY
         printf("CPU: CP0_TLBP returned %u\n",i);
         tlb_dump(cpu);
#endif
      }
   }
}
