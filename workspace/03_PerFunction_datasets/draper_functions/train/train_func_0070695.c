ppc32_exec_ADDO(cpu_ppc_t *cpu,ppc_insn_t insn)
{
   int rd = bits(insn,21,25);
   int ra = bits(insn,16,20);
   int rb = bits(insn,11,15);
   register m_uint32_t a,b,d;

   a = cpu->gpr[ra];
   b = cpu->gpr[rb];
   d = a + b;

   ppc32_exec_ov_sum(cpu,d,a,b);
   cpu->gpr[rd] = d;
   return(0);
}
