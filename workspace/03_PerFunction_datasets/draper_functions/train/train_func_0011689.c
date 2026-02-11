mips64_exec_BAL(cpu_mips_t *cpu,mips_insn_t insn)
{
   int offset = bits(insn,0,15);
   m_uint64_t new_pc;


   new_pc = (cpu->pc + 4) + sign_extend(offset << 2,18);


   cpu->gpr[MIPS_GPR_RA] = cpu->pc + 8;


   mips64_exec_bdslot(cpu);


   cpu->pc = new_pc;
   return(1);
}
