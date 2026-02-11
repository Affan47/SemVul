topcline(struct sstat *ss, struct pstat *ps, int nproc,
        time_t deltasec, time_t deltatic, time_t hz,
        int osvers, int osrel, int ossub, char *tstamp,
        int ppres,  int ntrun, int ntslpi, int ntslpu, int pexit, int pzombie)
{
	count_t		availcpu;

	if (!ps)
	{
		printf("report not available.....\n");
		return 0;
	}


	qsort(ps, ppres, sizeof(struct pstat), compcpu);

	availcpu  = ss->cpu.all.stime + ss->cpu.all.utime +
	            ss->cpu.all.ntime + ss->cpu.all.itime +
	            ss->cpu.all.wtime + ss->cpu.all.Itime +
		    ss->cpu.all.Stime + ss->cpu.all.steal +
		    ss->cpu.all.guest;

	availcpu /= ss->cpu.nrcpu;

	if (availcpu == 0)
		availcpu = 1;

	printf("%5d %-8.8s %3.0lf%% | %5d %-8.8s %3.0lf%% | "
	       "%5d %-8.8s %3.0lf%%\n",
		(ps+0)->gen.pid, (ps+0)->gen.name,
		(double)((ps+0)->cpu.stime + (ps+0)->cpu.utime)*100.0/availcpu,
		(ps+1)->gen.pid, (ps+1)->gen.name,
		(double)((ps+1)->cpu.stime + (ps+1)->cpu.utime)*100.0/availcpu,
		(ps+2)->gen.pid, (ps+2)->gen.name,
		(double)((ps+2)->cpu.stime + (ps+2)->cpu.utime)*100.0/availcpu);

	return 1;
}
