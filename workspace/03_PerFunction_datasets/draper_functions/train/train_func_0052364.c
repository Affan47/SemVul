dlite_tsymbols(int nargs, union arg_val_t args[],
	       struct regs_t *regs,
	       struct mem_t *mem)
{
  int i;

  if (nargs != 0)
    return "wrong number of arguments";


  sym_loadsyms(ld_prog_fname, FALSE);


  for (i=0; i<sym_ntextsyms; i++)
    sym_dumpsym(sym_textsyms[i], stdout);


  return NULL;
}
