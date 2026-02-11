mgmt_invalidate_icds(struct beiscsi_hba *phba,
				struct invalidate_command_table *inv_tbl,
				unsigned int num_invalidate, unsigned int cid,
				struct be_dma_mem *nonemb_cmd)

{
	struct be_ctrl_info *ctrl = &phba->ctrl;
	struct be_mcc_wrb *wrb;
	struct be_sge *sge;
	struct invalidate_commands_params_in *req;
	unsigned int i, tag = 0;

	spin_lock(&ctrl->mbox_lock);
	tag = alloc_mcc_tag(phba);
	if (!tag) {
		spin_unlock(&ctrl->mbox_lock);
		return tag;
	}

	req = nonemb_cmd->va;
	memset(req, 0, sizeof(*req));
	wrb = wrb_from_mccq(phba);
	sge = nonembedded_sgl(wrb);
	wrb->tag0 |= tag;

	be_wrb_hdr_prepare(wrb, sizeof(*req), false, 1);
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI,
			OPCODE_COMMON_ISCSI_ERROR_RECOVERY_INVALIDATE_COMMANDS,
			sizeof(*req));
	req->ref_handle = 0;
	req->cleanup_type = CMD_ISCSI_COMMAND_INVALIDATE;
	for (i = 0; i < num_invalidate; i++) {
		req->table[i].icd = inv_tbl->icd;
		req->table[i].cid = inv_tbl->cid;
		req->icd_count++;
		inv_tbl++;
	}
	sge->pa_hi = cpu_to_le32(upper_32_bits(nonemb_cmd->dma));
	sge->pa_lo = cpu_to_le32(nonemb_cmd->dma & 0xFFFFFFFF);
	sge->len = cpu_to_le32(nonemb_cmd->size);

	be_mcc_notify(phba);
	spin_unlock(&ctrl->mbox_lock);
	return tag;
}
