coroutine_yield(void *arg)
{
	struct coroutine *to = coroutine_self()->caller;
	if (!to) {
		fprintf(stderr, "Co-routine is yielding to no one\n");
		abort();
	}
	coroutine_self()->caller = NULL;
	return coroutine_swap(coroutine_self(), to, arg);
}
