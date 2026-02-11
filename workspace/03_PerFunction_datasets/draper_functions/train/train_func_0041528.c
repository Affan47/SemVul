mlx5_ib_poll_cq(struct ib_cq *ibcq, int num_entries, struct ib_wc *wc)
{
	struct mlx5_ib_cq *cq = to_mcq(ibcq);
	struct mlx5_ib_qp *cur_qp = NULL;
	unsigned long flags;
	int npolled;
	int err = 0;

	spin_lock_irqsave(&cq->lock, flags);

	for (npolled = 0; npolled < num_entries; npolled++) {
		err = mlx5_poll_one(cq, &cur_qp, wc + npolled);
		if (err)
			break;
	}

	if (npolled)
		mlx5_cq_set_ci(&cq->mcq);

	spin_unlock_irqrestore(&cq->lock, flags);

	if (err == 0 || err == -EAGAIN)
		return npolled;
	else
		return err;
}
