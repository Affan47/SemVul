mlx4_srq_free(struct mlx4_dev *dev, struct mlx4_srq *srq)
{
	struct mlx4_srq_table *srq_table = &mlx4_priv(dev)->srq_table;
	int err;

	err = mlx4_HW2SW_SRQ(dev, NULL, srq->srqn);
	if (err)
		mlx4_warn(dev, "HW2SW_SRQ failed (%d) for SRQN %06x\n", err, srq->srqn);

	spin_lock_irq(&srq_table->lock);
	radix_tree_delete(&srq_table->tree, srq->srqn);
	spin_unlock_irq(&srq_table->lock);

	if (atomic_dec_and_test(&srq->refcount))
		complete(&srq->free);
	wait_for_completion(&srq->free);

	mlx4_srq_free_icm(dev, srq->srqn);
}
