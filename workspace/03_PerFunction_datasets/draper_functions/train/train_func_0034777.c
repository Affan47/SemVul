rcu_pending(void)
{
	struct rcu_state *rsp;

	for_each_rcu_flavor(rsp)
		if (__rcu_pending(rsp, this_cpu_ptr(rsp->rda)))
			return 1;
	return 0;
}
