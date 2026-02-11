ppclose(FILE *frompgm, FILE *topgm)
{
#ifdef NeXT
  union wait w;
#else
  int w;
#endif
  unsigned int fd;
  int pid;

  if(frompgm == NULL) return -1;
  if(topgm) fclose(topgm);
  fd = fileno(frompgm);
  fclose(frompgm);
  if(fd < npps && pps[fd] != 0) {
	while((pid = wait(&w)) != pps[fd] && pid > 0)
	    ;
	pps[fd] = 0;
  }
  return 0;
}
