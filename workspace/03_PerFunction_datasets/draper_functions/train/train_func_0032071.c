ppc32_exec_DCBST(cpu_ppc_t *cpu,ppc_insn_t insn)
{
   int ra = bits(insn,16,20);
   int rb = bits(insn,11,15);
   m_uint32_t vaddr;

   vaddr = cpu->gpr[rb];

   if (ra != 0)
      vaddr += cpu->gpr[ra];


   return(0);
}
