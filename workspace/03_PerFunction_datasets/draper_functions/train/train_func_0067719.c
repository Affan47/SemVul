cmaes_WriteToFileAW(cmaes_t *t, const char *key, const char *name,
                         const char *appendwrite)
{
  const char *s = "tmpcmaes.dat";
  FILE *fp;

  if (name == 0)
    name = s;

  fp = fopen( name, appendwrite);

  if(fp == 0) {
    ERRORMESSAGE("cmaes_WriteToFile(): could not open '", name,
                 "' with flag ", appendwrite);
    return;
  }

  if (appendwrite[0] == 'w') {

    fprintf(fp, "%% # %s (randomSeed=%d, %s)\n", key, t->sp.seed, getTimeStr());
  } else
    if (t->gen > 0 || strncmp(name, "outcmaesfit", 11) != 0)
      cmaes_WriteToFilePtr(t, key, fp);

  fclose(fp);

}
