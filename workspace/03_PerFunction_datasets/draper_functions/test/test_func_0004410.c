mips64_dump_memory(cpu_mips_t *cpu,m_uint64_t vaddr,u_int count)
{
   void *haddr;
   u_int i;

   for(i=0;i<count;i++,vaddr+=4)
   {
      if ((i & 3) == 0)
         printf("\n  0x%16.16llx: ",vaddr);

      haddr = cpu->mem_op_lookup(cpu,vaddr);

      if (haddr)
         printf("0x%8.8x ",htovm32(*(m_uint32_t *)haddr));
      else
         printf("XXXXXXXXXX ");
   }

   printf("\n\n");
}
