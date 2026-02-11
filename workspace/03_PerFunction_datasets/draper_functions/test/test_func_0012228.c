print_syms(FILE *fp)
{
  struct sym_ent *p;
  int i;

  for (i = 0; i < SYM_TAB_SIZE; i++) {
    p = Sym_tab[i];
    while (p != NULL) {
      fprintf(fp, "%d  %s/%d, lex_val=%d\n", p->sym_num, p->name, p->arity, p->lex_val);
      p = p->next;
    }
  }
}
