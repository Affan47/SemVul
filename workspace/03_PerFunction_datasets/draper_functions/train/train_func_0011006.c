gen_new_symbol(char *prefix, int arity, Ilist syms)
{
  char name[MAX_NAME+20];
  int symnum;
  int i = 0;

  if (strlen(prefix) > MAX_NAME)
    fatal_error("gen_new_symbol, prefix is too big.");

  sprintf(name, "%s%d", prefix, i);
  symnum = str_to_sn(name, arity);

  while (ilist_member(syms, symnum)) {
    i++;
    sprintf(name, "%s%d", prefix, i);
    symnum = str_to_sn(name, arity);
  }

  return symnum;
}
