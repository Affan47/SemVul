mips64_exec_MFLO(cpu_mips_t *cpu,mips_insn_t insn)
{
   int rd = bits(insn,11,15);

   if (rd) cpu->gpr[rd] = cpu->lo;
   return(0);
}
