rcu_sync_init(struct rcu_sync *rsp, enum rcu_sync_type type)
{
	memset(rsp, 0, sizeof(*rsp));
	init_waitqueue_head(&rsp->gp_wait);
	rsp->gp_type = type;
}
