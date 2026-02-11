mlx4_HW2SW_SRQ_wrapper(struct mlx4_dev *dev, int slave,
			   struct mlx4_vhcr *vhcr,
			   struct mlx4_cmd_mailbox *inbox,
			   struct mlx4_cmd_mailbox *outbox,
			   struct mlx4_cmd_info *cmd)
{
	int err;
	int srqn = vhcr->in_modifier;
	struct res_srq *srq = NULL;

	err = srq_res_start_move_to(dev, slave, srqn, RES_SRQ_ALLOCATED, &srq);
	if (err)
		return err;
	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	if (err)
		goto ex_abort;
	atomic_dec(&srq->mtt->ref_count);
	if (srq->cq)
		atomic_dec(&srq->cq->ref_count);
	res_end_move(dev, slave, RES_SRQ, srqn);

	return 0;

ex_abort:
	res_abort_move(dev, slave, RES_SRQ, srqn);

	return err;
}
