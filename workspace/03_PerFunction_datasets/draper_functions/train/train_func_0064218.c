c4iw_count_rcqes(struct t4_cq *cq, struct t4_wq *wq, int *count)
{
	struct t4_cqe *cqe;
	u32 ptr;

	*count = 0;
	PDBG("%s count zero %d\n", __func__, *count);
	ptr = cq->sw_cidx;
	while (ptr != cq->sw_pidx) {
		cqe = &cq->sw_queue[ptr];
		if (RQ_TYPE(cqe) && (CQE_OPCODE(cqe) != FW_RI_READ_RESP) &&
		    (CQE_QPID(cqe) == wq->sq.qid) && cqe_completes_wr(cqe, wq))
			(*count)++;
		if (++ptr == cq->size)
			ptr = 0;
	}
	PDBG("%s cq %p count %d\n", __func__, cq, *count);
}
