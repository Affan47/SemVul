waitforjob(struct job *jp)
{
	int st;

	TRACE(("waitforjob(%%%d) called\n", jobno(jp)));
	while (jp->state == JOBRUNNING) {
		dowait(DOWAIT_BLOCK, jp);
	}
	st = getstatus(jp);
#if JOBS
	if (jp->jobctl) {
		xtcsetpgrp(ttyfd, rootpid);


		if (jp->sigint)
			raise(SIGINT);
	}
#endif
	if (! JOBS || jp->state == JOBDONE)
		freejob(jp);
	return st;
}
