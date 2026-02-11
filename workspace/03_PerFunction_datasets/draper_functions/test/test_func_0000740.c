bnxt_hwrm_reserve_tx_rings(struct bnxt *bp, int *tx_rings)
{
	struct hwrm_func_cfg_input req = {0};
	int rc;

	if (bp->hwrm_spec_code < 0x10601)
		return 0;

	if (BNXT_VF(bp))
		return 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_CFG, -1, -1);
	req.fid = cpu_to_le16(0xffff);
	req.enables = cpu_to_le32(FUNC_CFG_REQ_ENABLES_NUM_TX_RINGS);
	req.num_tx_rings = cpu_to_le16(*tx_rings);
	rc = hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (rc)
		return rc;

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = __bnxt_hwrm_get_tx_rings(bp, 0xffff, tx_rings);
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}
