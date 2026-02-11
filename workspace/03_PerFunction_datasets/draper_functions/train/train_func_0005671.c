mips64_exec_J(cpu_mips_t *cpu,mips_insn_t insn)
{
   u_int instr_index = bits(insn,0,25);
   m_uint64_t new_pc;


   new_pc = cpu->pc & ~((1 << 28) - 1);
   new_pc |= instr_index << 2;


   mips64_exec_bdslot(cpu);


   cpu->pc = new_pc;
   return(1);
}
