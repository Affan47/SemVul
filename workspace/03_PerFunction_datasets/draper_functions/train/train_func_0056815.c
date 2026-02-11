be_cmd_enable_magic_wol(struct be_adapter *adapter, u8 *mac,
			    struct be_dma_mem *nonemb_cmd)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_acpi_wol_magic_config *req;
	int status;

	spin_lock_bh(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}
	req = nonemb_cmd->va;

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ETH,
			       OPCODE_ETH_ACPI_WOL_MAGIC_CONFIG, sizeof(*req),
			       wrb, nonemb_cmd);
	memcpy(req->magic_mac, mac, ETH_ALEN);

	status = be_mcc_notify_wait(adapter);

err:
	spin_unlock_bh(&adapter->mcc_lock);
	return status;
}
