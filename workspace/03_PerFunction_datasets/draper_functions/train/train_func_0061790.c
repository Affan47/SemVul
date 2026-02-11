execute (aso, exp)
     Af_key *aso;
     Expr exp;
{
  char  *pav[128], *arg, pathName[PATH_MAX];
  int   i, j;
  Wait_t retcode;
  pid_t pid, wpid;

  strcpy (pathName, dirPrefix);
  if (af_retnumattr (aso, AF_ATTSTATE) == AF_BUSY)
    strcat (pathName, af_retattr (aso, AF_ATTUNIXNAME));
  else
    strcat (pathName, af_retattr (aso, AF_ATTBOUND));

  i = (int) exp->left;
  for (j = 0; strcmp((arg = nav[i++]), ";"); j++)
    if (!strcmp(arg, "{}"))
      pav[j] = pathName;
    else
      pav[j] = arg;

  pav[j] = (char *) NULL;
  if (j == 0) return 1;

  fflush(stdout);
  switch (pid = fork()) {
  case -1:
    sprintf (stMessage, "%s: fork failed\n", stProgramName);
    perror (stMessage);
    stExit (1);
    break;
  case 0:
    chdir(startDir);
    execvp(pav[0], pav);
    perror("vfind: exec failed");
    kill (getpid(), SIGHUP);
    _exit(127);
    break;
  default:
    while ((wpid = wait(&retcode)) != -1 && wpid != pid);
    if (WEXITSTATUS (retcode)) {
      fprintf(stderr, "%s: execution terminated\n", stProgramName);
      stExit (1);
    }
    return (!WEXITSTATUS (retcode));
    break;
  }


  return 0;
}
