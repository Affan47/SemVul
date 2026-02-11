bnxt_update_vf_mac(struct bnxt *bp)
{
	struct hwrm_func_qcaps_input req = {0};
	struct hwrm_func_qcaps_output *resp = bp->hwrm_cmd_resp_addr;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_QCAPS, -1, -1);
	req.fid = cpu_to_le16(0xffff);

	mutex_lock(&bp->hwrm_cmd_lock);
	if (_hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT))
		goto update_vf_mac_exit;


	if (!ether_addr_equal(resp->mac_address, bp->vf.mac_addr))
		memcpy(bp->vf.mac_addr, resp->mac_address, ETH_ALEN);


	if (is_valid_ether_addr(bp->vf.mac_addr))
		memcpy(bp->dev->dev_addr, bp->vf.mac_addr, ETH_ALEN);
update_vf_mac_exit:
	mutex_unlock(&bp->hwrm_cmd_lock);
}
