ppc32_exec_SRAWI_dot(cpu_ppc_t *cpu,ppc_insn_t insn)
{
   int rs = bits(insn,21,25);
   int ra = bits(insn,16,20);
   int sh = bits(insn,11,15);
   register m_uint32_t s,r,mask;

   cpu->xer_ca = 0;

   s = cpu->gpr[rs];
   r = (m_int32_t)s >> sh;
   mask = ~(0xFFFFFFFFU << sh);

   if ((s & 0x80000000) && ((s & mask) != 0))
      cpu->xer_ca = 1;

   ppc32_exec_update_cr0(cpu,r);
   cpu->gpr[ra] = r;
   return(0);
}
