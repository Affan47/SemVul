backtrace_handler(int n, siginfo_t *ist, void *extra) {
  static struct ucontext *puc;
  static void *btinfo[MAX_BTSIZE];
  static char **messages = NULL;
  static size_t btsize = 0;
  static size_t i;
  static char *strerr = "???";
  static FILE *fstrm;

  static char btpath[MAXPATHLEN];

  snprintf(btpath, MAXPATHLEN, "/tmp/hddtemp.backtrace.%d.XXXXXX", getpid());
  if( (fstrm = fdopen(mkstemp(btpath), "w")) == NULL)
    return;

#define SIC_CASE(c) case c: strerr = #c

  puc = (struct ucontext *)extra;
  switch(n) {
  case SIGSEGV:
    switch(ist->si_code) {
      SIC_CASE(SEGV_MAPERR);
      SIC_CASE(SEGV_ACCERR);
    }
    fprintf(fstrm, "=== SEGFAULT (%s) : invalid access to %p, in %p\n",
	    strerr,
	    ist->si_addr,
	    (void*)puc->uc_mcontext.gregs[REG_IP]);
    break;
  case SIGILL:
    switch(ist->si_code) {
      SIC_CASE(ILL_ILLOPC);
      SIC_CASE(ILL_ILLOPN);
      SIC_CASE(ILL_ILLADR);
      SIC_CASE(ILL_ILLTRP);
      SIC_CASE(ILL_PRVOPC);
      SIC_CASE(ILL_PRVREG);
      SIC_CASE(ILL_COPROC);
      SIC_CASE(ILL_BADSTK);
    }
    fprintf(fstrm, "=== ILLEGAL INSTR (%s) : invalid access to %p, in %p\n",
	    strerr,
	    ist->si_addr,
	    (void*)puc->uc_mcontext.gregs[REG_IP]);
    break;
  case SIGBUS:
    switch(ist->si_code) {
      SIC_CASE(BUS_ADRALN);
      SIC_CASE(BUS_ADRERR);
      SIC_CASE(BUS_OBJERR);
    }
    fprintf(fstrm, "=== BUS ERROR (%p) : invalid access to %p, in %p\n",
	    strerr,
	    ist->si_addr,
	    (void*)puc->uc_mcontext.gregs[REG_IP]);
    break;
  }
  fflush(fstrm);

#undef CASE


  btsize = backtrace(btinfo, MAX_BTSIZE);
  btinfo[1] = (void*) puc->uc_mcontext.gregs[REG_IP];

  messages = backtrace_symbols(btinfo, btsize);

  for(i = 1;
      i < btsize;
      i++)
    fprintf(fstrm, "[%d] #%zu: %s\n", getpid(), i, messages[i]);
  fflush(fstrm);
  fclose(fstrm);


}
