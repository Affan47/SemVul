ocrdma_mbx_mq_cq_create(struct ocrdma_dev *dev,
				   struct ocrdma_queue_info *cq,
				   struct ocrdma_queue_info *eq)
{
	struct ocrdma_create_cq_cmd *cmd = dev->mbx_cmd;
	struct ocrdma_create_cq_cmd_rsp *rsp = dev->mbx_cmd;
	int status;

	memset(cmd, 0, sizeof(*cmd));
	ocrdma_init_mch(&cmd->req, OCRDMA_CMD_CREATE_CQ,
			OCRDMA_SUBSYS_COMMON, sizeof(*cmd));

	cmd->req.rsvd_version = OCRDMA_CREATE_CQ_VER2;
	cmd->pgsz_pgcnt = (cq->size / OCRDMA_MIN_Q_PAGE_SIZE) <<
		OCRDMA_CREATE_CQ_PAGE_SIZE_SHIFT;
	cmd->pgsz_pgcnt |= PAGES_4K_SPANNED(cq->va, cq->size);

	cmd->ev_cnt_flags = OCRDMA_CREATE_CQ_DEF_FLAGS;
	cmd->eqn = eq->id;
	cmd->pdid_cqecnt = cq->size / sizeof(struct ocrdma_mcqe);

	ocrdma_build_q_pages(&cmd->pa[0], cq->size / OCRDMA_MIN_Q_PAGE_SIZE,
			     cq->dma, PAGE_SIZE_4K);
	status = be_roce_mcc_cmd(dev->nic_info.netdev,
				 cmd, sizeof(*cmd), NULL, NULL);
	if (!status) {
		cq->id = (u16) (rsp->cq_id & OCRDMA_CREATE_CQ_RSP_CQ_ID_MASK);
		cq->created = true;
	}
	return status;
}
