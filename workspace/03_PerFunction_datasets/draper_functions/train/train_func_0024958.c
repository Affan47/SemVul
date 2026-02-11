fil_fputs(var) VARIABLE *var;
{
  char *str = var_to_string(NEXT(var));
  int ind = *MATR(var);
  FILE *fp;

  if (ind < 0 || ind >= MAXFILES)
  {
    error("fputs: Invalid file number.\n");
  }
  else if (fil_fps[ind] == NULL)
  {
    error("fputs: File not open.\n");
  }
  fp = fil_fps[ind];

  fprintf(fp, "%s", str);

  FREEMEM(str);

  if (ferror(fp))
  {
    clearerr(fp);
    error("fprintf: error writing file.\n");
  }

  return (VARIABLE *)NULL;
}
