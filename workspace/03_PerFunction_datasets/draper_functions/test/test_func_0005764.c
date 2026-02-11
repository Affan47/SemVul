pad_wraparound(struct mlx4_ib_qp *qp, int ind)
{
	unsigned s = qp->sq.wqe_cnt - (ind & (qp->sq.wqe_cnt - 1));
	if (unlikely(s < qp->sq_max_wqes_per_wr)) {
		post_nop_wqe(qp, ind, s << qp->sq.wqe_shift);
		ind += s;
	}
	return ind;
}
