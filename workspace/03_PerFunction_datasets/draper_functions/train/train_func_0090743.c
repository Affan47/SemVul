ppc32_exec_SUBFC(cpu_ppc_t *cpu,ppc_insn_t insn)
{
   int rd = bits(insn,21,25);
   int ra = bits(insn,16,20);
   int rb = bits(insn,11,15);
   register m_uint32_t a,b,r,tmp;

   a = ~cpu->gpr[ra];
   b = cpu->gpr[rb];

   tmp = a + 1;
   r = b + tmp;

   ppc32_exec_ca_sum(cpu,tmp,a,1);
   if (r < tmp)
      cpu->xer_ca = 1;

   cpu->gpr[rd] = r;
   return(0);
}
