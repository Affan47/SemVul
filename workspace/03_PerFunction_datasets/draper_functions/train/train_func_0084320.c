freejob(n)
int n;
{
	if (n < 0 || n >= maxjobs) return;
	if (!(joblist[n].pids)) return;

	Xfree(joblist[n].pids);
	Xfree(joblist[n].stats);
	Xfree(joblist[n].fds);
	if (joblist[n].trp) {
		freestree(joblist[n].trp);
		Xfree(joblist[n].trp);
	}
	Xfree(joblist[n].tty);

	joblist[n].pids = NULL;
}
