rcu_sync_dtor(struct rcu_sync *rsp)
{
	int cb_state;

	BUG_ON(rsp->gp_count);

	spin_lock_irq(&rsp->rss_lock);
	if (rsp->cb_state == CB_REPLAY)
		rsp->cb_state = CB_PENDING;
	cb_state = rsp->cb_state;
	spin_unlock_irq(&rsp->rss_lock);

	if (cb_state != CB_IDLE) {
		gp_ops[rsp->gp_type].wait();
		BUG_ON(rsp->cb_state != CB_IDLE);
	}
}
