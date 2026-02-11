bnx2_poll_cnic(struct bnx2 *bp, struct bnx2_napi *bnapi)
{
	struct cnic_ops *c_ops;

	if (!bnapi->cnic_present)
		return;

	rcu_read_lock();
	c_ops = rcu_dereference(bp->cnic_ops);
	if (c_ops)
		bnapi->cnic_tag = c_ops->cnic_handler(bp->cnic_data,
						      bnapi->status_blk.msi);
	rcu_read_unlock();
}
