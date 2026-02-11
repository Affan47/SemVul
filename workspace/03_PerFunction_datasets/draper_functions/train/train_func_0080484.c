ppc32_exec_LSWI(cpu_ppc_t *cpu,ppc_insn_t insn)
{
   int rd = bits(insn,21,25);
   int ra = bits(insn,16,20);
   int nb = bits(insn,11,15);
   m_uint32_t vaddr = 0;
   int r;

   if (ra != 0)
      vaddr += cpu->gpr[ra];

   if (nb == 0)
      nb = 32;

   r = rd - 1;
   cpu->sw_pos = 0;

   while(nb > 0) {
      if (cpu->sw_pos == 0) {
         r = (r + 1) & 0x1F;
         cpu->gpr[r] = 0;
      }

      ppc32_exec_memop(cpu,PPC_MEMOP_LSW,vaddr,r);
      cpu->sw_pos += 8;

      if (cpu->sw_pos == 32)
         cpu->sw_pos = 0;

      vaddr++;
      nb--;
   }

   return(0);
}
