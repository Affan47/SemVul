__ibv_create_qp_1_0(struct ibv_pd_1_0 *pd,
				       struct ibv_qp_init_attr_1_0 *qp_init_attr)
{
	struct ibv_qp *real_qp;
	struct ibv_qp_1_0 *qp;
	struct ibv_qp_init_attr real_init_attr;

	qp = malloc(sizeof *qp);
	if (!qp)
		return NULL;

	real_init_attr.qp_context = qp_init_attr->qp_context;
	real_init_attr.send_cq    = qp_init_attr->send_cq->real_cq;
	real_init_attr.recv_cq    = qp_init_attr->recv_cq->real_cq;
	real_init_attr.srq        = qp_init_attr->srq ?
		qp_init_attr->srq->real_srq : NULL;
	real_init_attr.cap        = qp_init_attr->cap;
	real_init_attr.qp_type    = qp_init_attr->qp_type;
	real_init_attr.sq_sig_all = qp_init_attr->sq_sig_all;

	real_qp = ibv_create_qp(pd->real_pd, &real_init_attr);
	if (!real_qp) {
		free(qp);
		return NULL;
	}

	qp->context    = pd->context;
	qp->qp_context = qp_init_attr->qp_context;
	qp->pd         = pd;
	qp->send_cq    = qp_init_attr->send_cq;
	qp->recv_cq    = qp_init_attr->recv_cq;
	qp->srq        = qp_init_attr->srq;
	qp->qp_type    = qp_init_attr->qp_type;
	qp->qp_num     = real_qp->qp_num;
	qp->real_qp    = real_qp;

	qp_init_attr->cap = real_init_attr.cap;

	real_qp->qp_context = qp;

	return qp;
}
