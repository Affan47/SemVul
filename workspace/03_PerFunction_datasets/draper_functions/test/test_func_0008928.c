signalexit(sig)
int sig;
{
	signal2(sig, SIG_IGN);

	if (isorgpid()) {
		printf_urgent++;
		forcecleandir(deftmpdir, tmpfilename);
#ifdef	DEP_DOSDRIVE
		VOID_C dosallclose();
#endif
#ifdef	DEP_URLPATH
		VOID_C urlallclose();
#endif
#ifdef	DEP_LOGGING
		endlog(sig + 128);
#endif
		endterm();
		inittty(1);
		keyflush();
#ifdef	DEP_ORIGSHELL
# if	defined (SIGHUP) && !defined (NOJOB)
		if (sig == SIGHUP) killjob();
# endif
		prepareexit(0);
#endif
#ifdef	DEP_PTY
		killallpty();
#endif
#ifdef	DEBUG
# if	!MSDOS
		freeterment();
# endif
		closetty(&ttyio, &ttyout);
		muntrace();
#endif
		printf_urgent--;
	}

	signal2(sig, SIG_DFL);
	VOID_C kill(getpid(), sig);
}
