dofd(trp)
syntaxtree *trp;
{
	int n, mode;

	if (!shellmode || exit_status < 0) {
		execerror((trp -> comm) -> argv, NULL, ER_RECURSIVEFD, 0);
		return(RET_FAIL);
	}
	else if (dumbterm > 1) {
		execerror((trp -> comm) -> argv,
			getconstvar(ENVTERM), ER_INVALTERMFD, 1);
		return(RET_FAIL);
	}
	else if (!interactive || nottyout) {
		execerror((trp -> comm) -> argv, NULL, ER_INVALTERMFD, 1);
		return(RET_FAIL);
	}
	else {
		n = sigvecset(1);
		ttyiomode(0);
		mode = termmode(1);
		shellmode = 0;
		main_fd(&((trp -> comm) -> argv[1]), 1);
		shellmode = 1;
		VOID_C termmode(mode);
		stdiomode();
		VOID_C fputnl(Xstderr);
		sigvecset(n);
	}

	return(RET_SUCCESS);
}
