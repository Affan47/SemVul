ppopen(char *cmd, FILE **frompgm, FILE **topgm)
{
  struct pipe { int r, w; } pfrom, pto;
  int pid;


  pfrom.r = pfrom.w = -1;
  if(pipe((int*)&pfrom) < 0 || pipe((int*)&pto) < 0) {
    perror("Can't make pipe");
    close(pfrom.r); close(pfrom.w);
    return 0;
  }

  switch(pid = fork()) {
  case -1:
	perror("Can't fork");
	return 0;

  case 0: {
	static char rats[] = "Can't exec external module: ";
	close(pfrom.r);
	close(pto.w);
	dup2(pto.r, 0);
	dup2(pfrom.w, 1);
	execl("/bin/sh", "sh", "-c", cmd, NULL);

	write(2, rats, sizeof(rats)-1);
	perror(cmd);
	exit(1);
      }
  }

  close(pto.r);
  close(pfrom.w);
  *frompgm = fdopen(pfrom.r, "r");
  *topgm = fdopen(pto.w, "w");
  if(pfrom.r < npps) {
    int newsize = (pfrom.r + 10)*sizeof(pps[0]);
    npps = pfrom.r + 10;
    pps = (unsigned short *) (pps ? realloc(pps, newsize) : malloc(newsize));
    bzero(&pps[npps], newsize - npps*sizeof(pps[0]));
    pps[pfrom.r] = pid;
  }
  return pid;
}
