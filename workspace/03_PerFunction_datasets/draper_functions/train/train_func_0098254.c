__mlx4_ib_cq_clean(struct mlx4_ib_cq *cq, u32 qpn, struct mlx4_ib_srq *srq)
{
	u32 prod_index;
	int nfreed = 0;
	struct mlx4_cqe *cqe, *dest;
	u8 owner_bit;
	int cqe_inc = cq->buf.entry_size == 64 ? 1 : 0;


	for (prod_index = cq->mcq.cons_index; get_sw_cqe(cq, prod_index); ++prod_index)
		if (prod_index == cq->mcq.cons_index + cq->ibcq.cqe)
			break;


	while ((int) --prod_index - (int) cq->mcq.cons_index >= 0) {
		cqe = get_cqe(cq, prod_index & cq->ibcq.cqe);
		cqe += cqe_inc;

		if ((be32_to_cpu(cqe->vlan_my_qpn) & MLX4_CQE_QPN_MASK) == qpn) {
			if (srq && !(cqe->owner_sr_opcode & MLX4_CQE_IS_SEND_MASK))
				mlx4_ib_free_srq_wqe(srq, be16_to_cpu(cqe->wqe_index));
			++nfreed;
		} else if (nfreed) {
			dest = get_cqe(cq, (prod_index + nfreed) & cq->ibcq.cqe);
			dest += cqe_inc;

			owner_bit = dest->owner_sr_opcode & MLX4_CQE_OWNER_MASK;
			memcpy(dest, cqe, sizeof *cqe);
			dest->owner_sr_opcode = owner_bit |
				(dest->owner_sr_opcode & ~MLX4_CQE_OWNER_MASK);
		}
	}

	if (nfreed) {
		cq->mcq.cons_index += nfreed;


		wmb();
		mlx4_cq_set_ci(&cq->mcq);
	}
}
