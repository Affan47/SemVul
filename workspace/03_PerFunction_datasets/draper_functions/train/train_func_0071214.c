print_table_f1(FILE *fp, struct symbol *s)
{
  int i;
  char *s1, *s2;
  int n0 = s->args[0].n;

  if (n0 <= 10) {
    s1 = "%2d";
    s2 = "--";
  }
  else {
    s1 = "%3d";
    s2 = "---";
  }

  fprintf(fp, "\n %s :\n", s->name);
  fprintf(fp, "       ");
  for (i = 0; i < n0; i++)
    fprintf(fp, s1, i);
  fprintf(fp, "\n    ---");
  for (i = 0; i < n0; i++)
    fprintf(fp, s2);
  fprintf(fp, "\n       ");
  for (i = 0; i < n0; i++)
    fprintf(fp, s1, function_value_1(s, i));
  fprintf(fp, "\n");
}
