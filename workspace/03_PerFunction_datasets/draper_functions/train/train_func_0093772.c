read_time(bigint &ntimestep)
{
  char *eof = fgets(line,MAXLINE,fp);
  if (eof == NULL) return 1;

  if (strstr(line,"ITEM: TIMESTEP") != line)
    error->one(FLERR,"Dump file is incorrectly formatted");
  read_lines(1);
  sscanf(line,BIGINT_FORMAT,&ntimestep);

  return 0;
}
