mips64_exec_DIVU(cpu_mips_t *cpu,mips_insn_t insn)
{
   int rs = bits(insn,21,25);
   int rt = bits(insn,16,20);

   if (cpu->gpr[rt] == 0)
      return(0);

   cpu->lo = (m_uint32_t)cpu->gpr[rs] / (m_uint32_t)cpu->gpr[rt];
   cpu->hi = (m_uint32_t)cpu->gpr[rs] % (m_uint32_t)cpu->gpr[rt];

   cpu->lo = sign_extend(cpu->lo,32);
   cpu->hi = sign_extend(cpu->hi,32);
   return(0);
}
