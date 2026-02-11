beiscsi_cmd_eq_create(struct be_ctrl_info *ctrl,
			  struct be_queue_info *eq, int eq_delay)
{
	struct be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	struct be_cmd_req_eq_create *req = embedded_payload(wrb);
	struct be_cmd_resp_eq_create *resp = embedded_payload(wrb);
	struct be_dma_mem *q_mem = &eq->dma_mem;
	int status;

	spin_lock(&ctrl->mbox_lock);
	memset(wrb, 0, sizeof(*wrb));

	be_wrb_hdr_prepare(wrb, sizeof(*req), true, 0);

	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			OPCODE_COMMON_EQ_CREATE, sizeof(*req));

	req->num_pages = cpu_to_le16(PAGES_4K_SPANNED(q_mem->va, q_mem->size));

	AMAP_SET_BITS(struct amap_eq_context, func, req->context,
						PCI_FUNC(ctrl->pdev->devfn));
	AMAP_SET_BITS(struct amap_eq_context, valid, req->context, 1);
	AMAP_SET_BITS(struct amap_eq_context, size, req->context, 0);
	AMAP_SET_BITS(struct amap_eq_context, count, req->context,
					__ilog2_u32(eq->len / 256));
	AMAP_SET_BITS(struct amap_eq_context, delaymult, req->context,
					eq_delay_to_mult(eq_delay));
	be_dws_cpu_to_le(req->context, sizeof(req->context));

	be_cmd_page_addrs_prepare(req->pages, ARRAY_SIZE(req->pages), q_mem);

	status = be_mbox_notify(ctrl);
	if (!status) {
		eq->id = le16_to_cpu(resp->eq_id);
		eq->created = true;
	}
	spin_unlock(&ctrl->mbox_lock);
	return status;
}
