dlite_iregs(int nargs, union arg_val_t args[],
	    struct regs_t *regs,
	    struct mem_t *mem)
{
  char *err_str;

  if (nargs != 0)
    return "too many arguments";


  myfprintf(stdout, "PC: 0x%08p   NPC: 0x%08p\n",
	    regs->regs_PC, regs->regs_NPC);
  if ((err_str = dlite_cregs(nargs, args, regs, mem)) != NULL)
    return err_str;
  md_print_iregs(regs->regs_R, stdout);


  return NULL;
}
