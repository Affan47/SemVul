fil_save(ptr) VARIABLE *ptr;
{
  VARIABLE *tmp;
  char *file;
  FILE *fp;

  int i, j, ascflg = FALSE;

  file = var_to_string(ptr);

  if ((fp = fopen(file, "w")) == (FILE *)NULL)
  {
    error( "save: can't open file: %s.\n", file );
  }

  tmp = NEXT(ptr);

  if (NEXT(NEXT(ptr)) != (VARIABLE *)NULL)
    ascflg = M(NEXT(NEXT(ptr)), 0, 0);

  if (ascflg)
  {

    fprintf(fp, "%d %d %d %d\n", FILE_ASCII, TYPE(tmp), NROW(tmp), NCOL(tmp));
    if (ferror(fp))
    {
       fclose(fp); error("save: error writing file.\n");
    }

    for(i = 0; i < NROW(tmp); i++)
      for(j = 0; j < NCOL(tmp); j++)
      {
        fprintf(fp, "%e\n", M(tmp, i, j));
        if (ferror(fp))
        {
           fclose(fp); error("save: error writing file.\n");
        }
      }
  }

  else
  {

    fprintf(fp, "%d %d %d %d\n", FILE_BINARY, TYPE(tmp), NROW(tmp), NCOL(tmp));
    if (ferror(fp))
    {
       fclose(fp); error("save: error writing file.\n");
    }

    fwrite(MATR(tmp), 1, MATSIZE(tmp), fp);
    if (ferror(fp))
    {
       fclose(fp); error("save: error writing file.\n");
    }
  }

  fclose(fp); FREEMEM(file);

  return NULL;
}
