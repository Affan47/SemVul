_run_in_daemon(void)
{
	static bool set = false;
	static bool run = false;

	if (!set) {
		set = 1;
		run = run_in_daemon("slurmstepd");
	}

	return run;
}
