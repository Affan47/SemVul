_run_prog(char *prog, char *arg)
{
	int i;
	char program[1024], arg0[1024], arg1[1024], *pname;
	pid_t child;
	slurm_ctl_conf_t *ctlconf;

	if (prog == NULL)
		return -1;

	strncpy(program, prog, sizeof(program));
	pname = strrchr(program, '/');
	if (pname == NULL)
		pname = program;
	else
		pname++;
	strncpy(arg0, pname, sizeof(arg0));
	strncpy(arg1, arg, sizeof(arg1));

	child = fork();
	if (child == 0) {
		for (i=0; i<128; i++)
			close(i);
#ifdef SETPGRP_TWO_ARGS
		setpgrp(0, 0);
#else
		setpgrp();
#endif
		ctlconf = slurm_conf_lock();
		setenv("SLURM_CONF", ctlconf->slurm_conf, 1);
		slurm_conf_unlock();
		execl(program, arg0, arg1, NULL);
		exit(1);
	} else if (child < 0) {
		error("fork: %m");
	} else {

		for (i=0; i<PID_CNT; i++) {
			if (child_pid[i])
				continue;
			child_pid[i]  = child;
			child_time[i] = time(NULL);
			break;
		}
		if (i == PID_CNT)
			error("power_save: filled child_pid array");
	}
	return child;
}
