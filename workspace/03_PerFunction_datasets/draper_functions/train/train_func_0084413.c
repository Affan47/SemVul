rdma_fini(struct c4iw_dev *rhp, struct c4iw_qp *qhp,
		     struct c4iw_ep *ep)
{
	struct fw_ri_wr *wqe;
	int ret;
	struct sk_buff *skb;

	PDBG("%s qhp %p qid 0x%x tid %u\n", __func__, qhp, qhp->wq.sq.qid,
	     ep->hwtid);

	skb = alloc_skb(sizeof *wqe, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;
	set_wr_txq(skb, CPL_PRIORITY_DATA, ep->txq_idx);

	wqe = (struct fw_ri_wr *)__skb_put(skb, sizeof(*wqe));
	memset(wqe, 0, sizeof *wqe);
	wqe->op_compl = cpu_to_be32(
		FW_WR_OP_V(FW_RI_INIT_WR) |
		FW_WR_COMPL_F);
	wqe->flowid_len16 = cpu_to_be32(
		FW_WR_FLOWID_V(ep->hwtid) |
		FW_WR_LEN16_V(DIV_ROUND_UP(sizeof(*wqe), 16)));
	wqe->cookie = (uintptr_t)&ep->com.wr_wait;

	wqe->u.fini.type = FW_RI_TYPE_FINI;
	ret = c4iw_ofld_send(&rhp->rdev, skb);
	if (ret)
		goto out;

	ret = c4iw_wait_for_reply(&rhp->rdev, &ep->com.wr_wait, qhp->ep->hwtid,
			     qhp->wq.sq.qid, __func__);
out:
	PDBG("%s ret %d\n", __func__, ret);
	return ret;
}
