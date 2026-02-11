mono_threads_get_max_stack_size (void)
{
	struct rlimit lim;


	if (getrlimit (RLIMIT_STACK, &lim))
		return INT_MAX;

	if (lim.rlim_max > (rlim_t)INT_MAX)
		return INT_MAX;
	return (int)lim.rlim_max;
}
