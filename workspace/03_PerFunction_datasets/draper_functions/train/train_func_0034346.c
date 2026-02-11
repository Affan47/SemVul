mips64_mts64_translate(cpu_mips_t *cpu,m_uint64_t vaddr,
                                           m_uint32_t *phys_page)
{
   mts64_entry_t *entry,alt_entry;
   m_uint32_t hash_bucket;
   m_uint64_t data = 0;

   hash_bucket = MTS64_HASH(vaddr);
   entry = &cpu->mts_u.mts64_cache[hash_bucket];


   if (unlikely((vaddr & MIPS_MIN_PAGE_MASK) != entry->gvpa)) {
      entry = mips64_mts64_slow_lookup(cpu,vaddr,MIPS_MEMOP_LOOKUP,4,MTS_READ,
                                       &data,&alt_entry);
      if (!entry)
         return(-1);
   }

   *phys_page = entry->gppa >> MIPS_MIN_PAGE_SHIFT;
   return(0);
}
