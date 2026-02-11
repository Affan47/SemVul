knode_can_recontact(const knode_t *kn)
{
	time_t grace;
	time_delta_t elapsed;

	knode_check(kn);

	if (!kn->rpc_timeouts)
		return TRUE;

	grace = 1 << kn->rpc_timeouts;
	elapsed = delta_time(tm_time(), kn->last_sent);

	return elapsed > grace;
}
