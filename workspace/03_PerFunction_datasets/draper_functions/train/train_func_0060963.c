function_value_3(struct symbol *s, int i, int j, int a)
{
  int b, k;
  int n3 = s->args[3].n;

  b = ATOM4(s, i, j, a, 0);
  for (k = 0; k < n3 && atom_value(b+k) != 1; k++);
  return(k == n3 ? -1 : k);
}
