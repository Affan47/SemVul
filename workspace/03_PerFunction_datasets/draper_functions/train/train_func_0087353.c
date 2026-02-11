ppc32_exec_STSWX(cpu_ppc_t *cpu,ppc_insn_t insn)
{
   int rs = bits(insn,21,25);
   int ra = bits(insn,16,20);
   int rb = bits(insn,11,15);
   m_uint32_t vaddr;
   int r,nb;

   vaddr = cpu->gpr[rb];

   if (ra != 0)
      vaddr += cpu->gpr[ra];

   nb = cpu->xer & PPC32_XER_BC_MASK;
   r = rs - 1;
   cpu->sw_pos = 0;

   while(nb > 0) {
      if (cpu->sw_pos == 0)
         r = (r + 1) & 0x1F;

      ppc32_exec_memop(cpu,PPC_MEMOP_STSW,vaddr,r);
      cpu->sw_pos += 8;

      if (cpu->sw_pos == 32)
         cpu->sw_pos = 0;

      vaddr++;
      nb--;
   }

   return(0);
}
