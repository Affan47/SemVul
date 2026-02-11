__ibv_query_qp_1_0(struct ibv_qp_1_0 *qp, struct ibv_qp_attr *attr,
		       int attr_mask,
		       struct ibv_qp_init_attr_1_0 *init_attr)
{
	struct ibv_qp_init_attr real_init_attr;
	int ret;

	ret = ibv_query_qp(qp->real_qp, attr, attr_mask, &real_init_attr);
	if (ret)
		return ret;

	init_attr->qp_context = qp->qp_context;
	init_attr->send_cq    = real_init_attr.send_cq->cq_context;
	init_attr->recv_cq    = real_init_attr.recv_cq->cq_context;
	init_attr->srq        = real_init_attr.srq->srq_context;
	init_attr->qp_type    = real_init_attr.qp_type;
	init_attr->cap        = real_init_attr.cap;
	init_attr->sq_sig_all = real_init_attr.sq_sig_all;

	return 0;
}
