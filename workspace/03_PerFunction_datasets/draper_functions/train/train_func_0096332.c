callmacro(command, arg, flags)
CONST char *command, *arg;
int flags;
{
	int i, n;

	if (parentfd < 0) {
		changewin(MAXWINDOWS, (p_id_t)-1);
		if (ptymode) {
			hideclock = 2;
			warning(0, NOPTY_K);
		}
		killpty(win, NULL);
		for (i = 0; i < MAXWINDOWS; i++) if (ptylist[i].pid) break;
		if (i < MAXWINDOWS) {
			hideclock = 2;
			if (!yesno(KILL_K)) return(-1);
		}
		killallpty();
	}

	if (flags & F_DOSYSTEM) n = dosystem(command);
#ifndef	DEP_ORIGSHELL
	else if (flags & F_EVALMACRO) n = execusercomm(command, arg, flags);
#endif
	else n = execmacro(command, arg, flags);

	return(n);
}
