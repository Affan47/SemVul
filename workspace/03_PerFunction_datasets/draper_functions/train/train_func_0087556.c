declare_symbol_sorted(char *name, int arity, char at[][MAX_MNAME])
{
  int i, j, m;
  struct symbol *s;

  if (Num_symbols == MAX_SYMBOLS)
    MACE_abend("declare_symbol_sorted, too many symbols");

  s = Symbols + Num_symbols;
  Num_symbols++;
  strcpy(s->name, name);
  s->arity = arity;
  s->base = Next_base;
  s->assigned_value = -1;

  for (i = 0; i < arity; i++) {
    j = sort_index(at[i]);
    if (j == -1) {
      printf("%s", at[i]);
      MACE_abend("declare_symbol_sorted: sort not found");
    }
    s->args[i].sort = j;
    s->args[i].n = Sorts[j].n;
  }

  for (i = arity-1, m = 1; i >= 0; i--) {
    s->args[i].mult = m;
    m = m * s->args[i].n;
  }
  s->end = (s->base + m) - 1;

  Next_base += m;
  return(Num_symbols-1);
}
