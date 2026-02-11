pcmd(int argc, char **argv)

{
  int	ai;
  int	i;
  int	j;
  KWD	*k;

  k = cmdkwds;
  ai = 0;
  cmdi = 0;
  while (ai < argc) {
    i = findkwd(argv[ai], k);
    if (i == -1)
      return GLOBUS_SUCCESS;
    cmds[cmdi++] = k[i].kwd;
    ai++;
    if (k[i].nextkwd) {
      k = k[i].nextkwd;
      continue;
    }
    if (argc - ai != k[i].narg && k[i].narg >= 0) {
      if (argc - ai < k[i].narg)
	fprintf(stderr, "Incomplete command:");
      else
	fprintf(stderr, "Too many arguments:");
      for (j = 0; j < cmdi; j++)
	fprintf(stderr, " %s", cmds[j]);
      if (k[i].arghelp)
	fprintf(stderr, " %s", k[i].arghelp);
      fprintf(stderr, "\n");
      return GLOBUS_SUCCESS;
    }
    return k[i].f(argc - ai, &argv[ai]);
  }
  if (cmdi) {
    fprintf(stderr, "Incomplete command:\n");
    showcmds(cmdi, cmds, k);
  }
  return GLOBUS_SUCCESS;
}
