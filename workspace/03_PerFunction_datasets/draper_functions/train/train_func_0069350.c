mlx5_srq_event(struct mlx5_core_dev *dev, u32 srqn, int event_type)
{
	struct mlx5_srq_table *table = &dev->priv.srq_table;
	struct mlx5_core_srq *srq;

	spin_lock(&table->lock);

	srq = radix_tree_lookup(&table->tree, srqn);
	if (srq)
		atomic_inc(&srq->refcount);

	spin_unlock(&table->lock);

	if (!srq) {
		mlx5_core_warn(dev, "Async event for bogus SRQ 0x%08x\n", srqn);
		return;
	}

	srq->event(srq, event_type);

	if (atomic_dec_and_test(&srq->refcount))
		complete(&srq->free);
}
