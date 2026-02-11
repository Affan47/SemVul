mlx4_ib_post_recv(struct ib_qp *ibqp, struct ib_recv_wr *wr,
		      struct ib_recv_wr **bad_wr)
{
	struct mlx4_ib_qp *qp = to_mqp(ibqp);
	struct mlx4_wqe_data_seg *scat;
	unsigned long flags;
	int err = 0;
	int nreq;
	int ind;
	int max_gs;
	int i;
	struct mlx4_ib_dev *mdev = to_mdev(ibqp->device);

	max_gs = qp->rq.max_gs;
	spin_lock_irqsave(&qp->rq.lock, flags);

	if (mdev->dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR) {
		err = -EIO;
		*bad_wr = wr;
		nreq = 0;
		goto out;
	}

	ind = qp->rq.head & (qp->rq.wqe_cnt - 1);

	for (nreq = 0; wr; ++nreq, wr = wr->next) {
		if (mlx4_wq_overflow(&qp->rq, nreq, qp->ibqp.recv_cq)) {
			err = -ENOMEM;
			*bad_wr = wr;
			goto out;
		}

		if (unlikely(wr->num_sge > qp->rq.max_gs)) {
			err = -EINVAL;
			*bad_wr = wr;
			goto out;
		}

		scat = get_recv_wqe(qp, ind);

		if (qp->mlx4_ib_qp_type & (MLX4_IB_QPT_PROXY_SMI_OWNER |
		    MLX4_IB_QPT_PROXY_SMI | MLX4_IB_QPT_PROXY_GSI)) {
			ib_dma_sync_single_for_device(ibqp->device,
						      qp->sqp_proxy_rcv[ind].map,
						      sizeof (struct mlx4_ib_proxy_sqp_hdr),
						      DMA_FROM_DEVICE);
			scat->byte_count =
				cpu_to_be32(sizeof (struct mlx4_ib_proxy_sqp_hdr));

			scat->lkey = cpu_to_be32(wr->sg_list->lkey);
			scat->addr = cpu_to_be64(qp->sqp_proxy_rcv[ind].map);
			scat++;
			max_gs--;
		}

		for (i = 0; i < wr->num_sge; ++i)
			__set_data_seg(scat + i, wr->sg_list + i);

		if (i < max_gs) {
			scat[i].byte_count = 0;
			scat[i].lkey       = cpu_to_be32(MLX4_INVALID_LKEY);
			scat[i].addr       = 0;
		}

		qp->rq.wrid[ind] = wr->wr_id;

		ind = (ind + 1) & (qp->rq.wqe_cnt - 1);
	}

out:
	if (likely(nreq)) {
		qp->rq.head += nreq;


		wmb();

		*qp->db.db = cpu_to_be32(qp->rq.head & 0xffff);
	}

	spin_unlock_irqrestore(&qp->rq.lock, flags);

	return err;
}
