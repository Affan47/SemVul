init() {


      {
	      basepf.nextc = basepf.buf = basebuf;
      }


      {
	      sigmode[SIGCHLD - 1] = S_DFL;
	      setsignal(SIGCHLD);
      }


      {
#ifdef USE_GLIBC_STDIO
	      initstreams();
#endif
      }


      {
	      char **envp;
	      static char ppid[32] = "PPID=";
	      const char *p;
	      struct stat st1, st2;

	      initvar();
	      for (envp = environ ; *envp ; envp++) {
		      if (strchr(*envp, '=')) {
			      setvareq(*envp, VEXPORT|VTEXTFIXED);
		      }
	      }

	      fmtstr(ppid + 5, sizeof(ppid) - 5, "%ld", (long) getppid());
	      setvareq(ppid, VTEXTFIXED);

	      p = lookupvar("PWD");
	      if (p)
		      if (*p != '/' || stat(p, &st1) || stat(".", &st2) ||
			  st1.st_dev != st2.st_dev || st1.st_ino != st2.st_ino)
			      p = 0;
	      setpwd(p, 0);
      }
}
