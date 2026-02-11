savefeedback(void)
{
	PIDTYPE	fpid;
	int	pfs[2];
	FILE	*infile;
	char	in_line[80];

	if  (pipe(pfs) < 0)
		return  0;
	if  (!(infile = fdopen(pfs[0], "r")))  {
		close(pfs[0]);
		close(pfs[1]);
		return  0;
	}
	fpid = fork();
	if  (fpid < 0)  {
		fclose(infile);
		close(pfs[1]);
		return  0;
	}
	if  (fpid != 0)  {
		close(2);
		if  (dup(pfs[1]) < 0)  {
			kill(fpid, SIGKILL);
			close(pfs[0]);
			close(pfs[1]);
			return  0;
		}
		fclose(infile);
		close(pfs[1]);
		return  1;
	}


	close(pfile);
	close(pfs[1]);
	set_signal(DAEMSTOP, SIG_DFL);
	set_signal(SIGPIPE, SIG_DFL);
	set_signal(SIGHUP, SIG_DFL);
	set_signal(SIGALRM, SIG_DFL);
	set_signal(DAEMRST, SIG_IGN);

	while  (fgets(in_line, sizeof(in_line), infile))  {
		int	l = strlen(in_line) - 1;
		if  (in_line[l] == '\n')
			in_line[l] = '\0';
		if  (in_params.pi_flags & PI_LOGERROR)  {
			disp_str = pathn;
			disp_str2 = prtnam;
			nfreport(1028);
			disp_str = in_line;
			nfreport(1029);
		}
		if  (in_params.pi_flags & PI_FBERROR)
			strncpy(Pptr->spp_feedback, in_line, PFEEDBACK);
	}
	exit(0);
}
