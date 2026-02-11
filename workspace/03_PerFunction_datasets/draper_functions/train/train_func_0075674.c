cxio_rdma_init(struct cxio_rdev *rdev_p, struct t3_rdma_init_attr *attr)
{
	struct t3_rdma_init_wr *wqe;
	struct sk_buff *skb = alloc_skb(sizeof(*wqe), GFP_ATOMIC);
	if (!skb)
		return -ENOMEM;
	PDBG("%s rdev_p %p\n", __func__, rdev_p);
	wqe = (struct t3_rdma_init_wr *) __skb_put(skb, sizeof(*wqe));
	wqe->wrh.op_seop_flags = cpu_to_be32(V_FW_RIWR_OP(T3_WR_INIT));
	wqe->wrh.gen_tid_len = cpu_to_be32(V_FW_RIWR_TID(attr->tid) |
					   V_FW_RIWR_LEN(sizeof(*wqe) >> 3));
	wqe->wrid.id1 = 0;
	wqe->qpid = cpu_to_be32(attr->qpid);
	wqe->pdid = cpu_to_be32(attr->pdid);
	wqe->scqid = cpu_to_be32(attr->scqid);
	wqe->rcqid = cpu_to_be32(attr->rcqid);
	wqe->rq_addr = cpu_to_be32(attr->rq_addr - rdev_p->rnic_info.rqt_base);
	wqe->rq_size = cpu_to_be32(attr->rq_size);
	wqe->mpaattrs = attr->mpaattrs;
	wqe->qpcaps = attr->qpcaps;
	wqe->ulpdu_size = cpu_to_be16(attr->tcp_emss);
	wqe->rqe_count = cpu_to_be16(attr->rqe_count);
	wqe->flags_rtr_type = cpu_to_be16(attr->flags |
					  V_RTR_TYPE(attr->rtr_type) |
					  V_CHAN(attr->chan));
	wqe->ord = cpu_to_be32(attr->ord);
	wqe->ird = cpu_to_be32(attr->ird);
	wqe->qp_dma_addr = cpu_to_be64(attr->qp_dma_addr);
	wqe->qp_dma_size = cpu_to_be32(attr->qp_dma_size);
	wqe->irs = cpu_to_be32(attr->irs);
	skb->priority = 0;
	return iwch_cxgb3_ofld_send(rdev_p->t3cdev_p, skb);
}
