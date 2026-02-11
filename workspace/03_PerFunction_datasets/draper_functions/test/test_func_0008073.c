lineindex(Vect *pline)
{
  int i,j;
  int n = 0;
  for (i = 0; i < pline->nvec; i++) {
    for (j = 0; j < pline->vnvert[i]; j++) {
      fprintf(f, " %d, ", n++);
    }
    fprintf(f, " -1,\n ");
  }
}
