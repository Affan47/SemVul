outcontrol(z)
double *z;
{
  int i, j;

  j = 0;
  for (i = 0; i < n; i++) {
    fprintf(outfile, "% .5e", z[i]);
    j++;
    if (j == 4) {
      putc('\n', outfile);
      j = 0;
    }
  }
  if (j != 0)
    putc('\n', outfile);
}
