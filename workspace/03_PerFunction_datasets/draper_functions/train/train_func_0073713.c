round_jiffies_common(unsigned long j, int cpu,
		bool force_up)
{
	int rem;
	unsigned long original = j;


	j += cpu * 3;

	rem = j % HZ;


	if (rem < HZ/4 && !force_up)
		j = j - rem;
	else
		j = j - rem + HZ;


	j -= cpu * 3;


	return time_is_after_jiffies(j) ? j : original;
}
