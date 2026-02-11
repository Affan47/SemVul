be_cmd_manage_iface(struct be_adapter *adapter, u32 iface, u8 op)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_manage_iface_filters *req;
	int status;

	if (iface == 0xFFFFFFFF)
		return -1;

	spin_lock_bh(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}
	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			       OPCODE_COMMON_MANAGE_IFACE_FILTERS, sizeof(*req),
			       wrb, NULL);
	req->op = op;
	req->target_iface_id = cpu_to_le32(iface);

	status = be_mcc_notify_wait(adapter);
err:
	spin_unlock_bh(&adapter->mcc_lock);
	return status;
}
