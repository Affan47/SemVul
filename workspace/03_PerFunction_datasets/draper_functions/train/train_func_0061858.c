compute_perfect_interleave(void)
{
	double smallest = cycles_to_sec[0];
	int cpunum;


	perfect_interleave = 1.0;
	for (cpunum = 1; Machine->drv->cpu[cpunum].cpu_type != CPU_DUMMY; cpunum++)
	{

		if (cycles_to_sec[cpunum] < smallest)
		{
			perfect_interleave = smallest;
			smallest = cycles_to_sec[cpunum];
		}
		else if (cycles_to_sec[cpunum] < perfect_interleave)
			perfect_interleave = cycles_to_sec[cpunum];
	}


	if (perfect_interleave == 1.0)
		perfect_interleave = cycles_to_sec[0];

	LOG(("Perfect interleave = %.9f, smallest = %.9f\n", perfect_interleave, smallest));
}
