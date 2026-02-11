tweak_stack_size(struct cli *cli, const struct parspec *par,
    const char *arg)
{
	unsigned low, u;
	char buf[12];

	low = sysconf(_SC_THREAD_STACK_MIN);

	if (arg != NULL && !strcmp(arg, "32bit")) {
		u = 65536;
		if (u < low)
			u = low;
		sprintf(buf, "%u", u);
		arg = buf;
	}

	tweak_generic_uint(cli, &master.wthread_stacksize, arg,
	    low, (uint)par->max);
}
