Father_Pred_Of_Aux(int func, int *father_arity)
{
  char *p;
  int l;

  p = Detect_If_Aux_Name(func);
  if (p == NULL)
    return -1;

  l = p - atom_tbl[func].name;

  *father_arity = strtol(p + 1, NULL, 10);
  strcpy(glob_buff, atom_tbl[func].name + 1);
  glob_buff[l - 1] = '\0';

  return Create_Allocate_Atom(glob_buff);
}
