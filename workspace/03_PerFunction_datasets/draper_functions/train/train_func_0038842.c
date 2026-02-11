searchjob(pid, np)
p_id_t pid;
int *np;
{
	int i, n;

	for (n = 0; n < maxjobs; n++) {
		if (!(joblist[n].pids)) continue;
		for (i = 0; i <= joblist[n].npipe; i++) {
			if (joblist[n].pids[i] != pid) continue;
			if (np) *np = i;
			return(n);
		}
	}

	return(-1);
}
