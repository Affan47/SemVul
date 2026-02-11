pmacroexec(const char *str, const struct spptr *pp)
{
	PIDTYPE	pid;
	int	status;

	if  (!execprog)
		execprog = envprocess(EXECPROG);

	if  ((pid = fork()) == 0)  {
		char	*argbuf[3];
		char	nbuf[PTRNAMESIZE+HOSTNSIZE+2];
		argbuf[0] = (char *) str;
		if  (pp)  {
			if  (pp->spp_netid)  {
				sprintf(nbuf, "%s:%s", look_host(pp->spp_netid), pp->spp_ptr);
				argbuf[1] = nbuf;
			}
			else
				argbuf[1] = (char *) pp->spp_ptr;
			argbuf[2] = (char *) 0;
		}
		else
			argbuf[1] = (char *) 0;
		chdir(Curr_pwd);
		execv(execprog, argbuf);
		exit(255);
	}
	if  (pid < 0)  {
		doerror(3071);
		return  0;
	}
#ifdef	HAVE_WAITPID
	while  (waitpid(pid, &status, 0) < 0)
		;
#else
	while  (wait(&status) != pid)
		;
#endif
	if  (status != 0)  {
		if  (status & 255)  {
			disp_arg[0] = status & 255;
			doerror(3072);
		}
		else  {
			disp_arg[0] = (status >> 8) & 255;
			doerror(3073);
		}
		return  0;
	}

	return  1;
}
