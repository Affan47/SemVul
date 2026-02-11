mips64_exec_LD(cpu_mips_t *cpu,mips_insn_t insn)
{
   int base   = bits(insn,21,25);
   int rt     = bits(insn,16,20);
   int offset = bits(insn,0,15);

   mips64_exec_memop2(cpu,MIPS_MEMOP_LD,base,offset,rt,TRUE);
   return(0);
}
