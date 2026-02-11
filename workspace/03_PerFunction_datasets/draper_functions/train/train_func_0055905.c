alberta_matrix(size_t nr, size_t nc, size_t size,
		      const char *fct, const char *file, int line)
{
  int       i;
  size_t    row_length = nc*size;
  char      **mat, *mrows;

  mat = (char **) alberta_alloc(nr*sizeof(char *), fct, file, line);
  mrows = (char *) alberta_alloc(nr*nc*size, fct, file, line);

  for(i = 0; i < nr; i++)
    mat[i] = mrows + i*row_length;

  return((void **)mat);
}
