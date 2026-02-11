dlite_status(md_addr_t regs_PC,
	     md_addr_t next_PC,
	     counter_t cycle,
	     int dbreak,
	     struct regs_t *regs,
	     struct mem_t *mem)
{
  md_inst_t inst;
  char *errstr;

  if (dbreak)
    {
      fprintf(stdout, "\n");
      fprintf(stdout, "Instruction (now finished) that caused data break:\n");
      myfprintf(stdout, "[%10n] 0x%08p:    ", cycle, regs_PC);
      errstr =
	f_dlite_mem_obj(mem, FALSE,
			regs_PC, (char *)&inst, sizeof(inst));
      inst = MD_SWAPI(inst);
      if (errstr)
	fprintf(stdout, "<invalid memory>: %s", errstr);
      else
	md_print_insn(inst, regs_PC, stdout);
      fprintf(stdout, "\n");
      fprintf(stdout, "\n");
    }


  myfprintf(stdout, "[%10n] 0x%08p:    ", cycle, next_PC);
  errstr =
    f_dlite_mem_obj(mem, FALSE,
		    next_PC, (char *)&inst, sizeof(inst));
  inst = MD_SWAPI(inst);
  if (errstr)
    fprintf(stdout, "<invalid memory>: %s", errstr);
  else
    md_print_insn(inst, next_PC, stdout);
  fprintf(stdout, "\n");
}
