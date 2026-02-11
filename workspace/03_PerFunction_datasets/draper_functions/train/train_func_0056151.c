beiscsi_cmd_cq_create(struct be_ctrl_info *ctrl,
			  struct be_queue_info *cq, struct be_queue_info *eq,
			  bool sol_evts, bool no_delay, int coalesce_wm)
{
	struct be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	struct be_cmd_req_cq_create *req = embedded_payload(wrb);
	struct be_cmd_resp_cq_create *resp = embedded_payload(wrb);
	struct beiscsi_hba *phba = pci_get_drvdata(ctrl->pdev);
	struct be_dma_mem *q_mem = &cq->dma_mem;
	void *ctxt = &req->context;
	int status;

	spin_lock(&ctrl->mbox_lock);
	memset(wrb, 0, sizeof(*wrb));

	be_wrb_hdr_prepare(wrb, sizeof(*req), true, 0);

	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			OPCODE_COMMON_CQ_CREATE, sizeof(*req));

	req->num_pages = cpu_to_le16(PAGES_4K_SPANNED(q_mem->va, q_mem->size));
	if (is_chip_be2_be3r(phba)) {
		AMAP_SET_BITS(struct amap_cq_context, coalescwm,
			      ctxt, coalesce_wm);
		AMAP_SET_BITS(struct amap_cq_context, nodelay, ctxt, no_delay);
		AMAP_SET_BITS(struct amap_cq_context, count, ctxt,
			      __ilog2_u32(cq->len / 256));
		AMAP_SET_BITS(struct amap_cq_context, valid, ctxt, 1);
		AMAP_SET_BITS(struct amap_cq_context, solevent, ctxt, sol_evts);
		AMAP_SET_BITS(struct amap_cq_context, eventable, ctxt, 1);
		AMAP_SET_BITS(struct amap_cq_context, eqid, ctxt, eq->id);
		AMAP_SET_BITS(struct amap_cq_context, armed, ctxt, 1);
		AMAP_SET_BITS(struct amap_cq_context, func, ctxt,
			      PCI_FUNC(ctrl->pdev->devfn));
	} else {
		req->hdr.version = MBX_CMD_VER2;
		req->page_size = 1;
		AMAP_SET_BITS(struct amap_cq_context_v2, coalescwm,
			      ctxt, coalesce_wm);
		AMAP_SET_BITS(struct amap_cq_context_v2, nodelay,
			      ctxt, no_delay);
		AMAP_SET_BITS(struct amap_cq_context_v2, count, ctxt,
			      __ilog2_u32(cq->len / 256));
		AMAP_SET_BITS(struct amap_cq_context_v2, valid, ctxt, 1);
		AMAP_SET_BITS(struct amap_cq_context_v2, eventable, ctxt, 1);
		AMAP_SET_BITS(struct amap_cq_context_v2, eqid, ctxt, eq->id);
		AMAP_SET_BITS(struct amap_cq_context_v2, armed, ctxt, 1);
	}

	be_dws_cpu_to_le(ctxt, sizeof(req->context));

	be_cmd_page_addrs_prepare(req->pages, ARRAY_SIZE(req->pages), q_mem);

	status = be_mbox_notify(ctrl);
	if (!status) {
		cq->id = le16_to_cpu(resp->cq_id);
		cq->created = true;
	} else
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BC_%d : In be_cmd_cq_create, status=ox%08x\n",
			    status);

	spin_unlock(&ctrl->mbox_lock);

	return status;
}
