rcu_gp_in_progress(struct rcu_state *rsp)
{
	return READ_ONCE(rsp->completed) != READ_ONCE(rsp->gpnum);
}
