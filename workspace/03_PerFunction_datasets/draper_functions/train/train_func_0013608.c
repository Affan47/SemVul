popen_r(const char* cmd, pid_t* pid)
{
    int     p[2];
    register int myside, yourside;

    if (pipe(p) < 0) {
    	return -1;
    }

    myside   = p[RDR];
    yourside = p[WTR];

    if( ((*pid) = fork()) == 0) {


     	(void) close(myside);
    	(void) close(STDOUT_FILENO);
    	(void) fcntl(yourside, F_DUPFD, STDOUT_FILENO);
    	(void) close(yourside);
    	(void) execl(bin_shell, shell, shflg, cmd, (char *)0);
    	_exit(1);
    }
    if ((*pid) == -1) {
        return -1;
    }
    (void) close(yourside);

    return myside;
}
