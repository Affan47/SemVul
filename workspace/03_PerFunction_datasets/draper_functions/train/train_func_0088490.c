print_table_r0_ivy(FILE *fp, struct symbol *s)
{
  int v;
  char *s1;
  v = atom_value(ATOM0(s));
  switch(v) {
  case 0: s1 = "nil"; break;
  case 1: s1 = "t"; break;
  case 2: s1 = "nil"; break;
  default: s1 = "?"; break;
  }
  fprintf(fp, "   ((%s . 0) . ((nil . %s)))\n", s->name, s1);
}
