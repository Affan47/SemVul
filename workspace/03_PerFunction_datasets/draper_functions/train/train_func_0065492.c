bnxt_approve_mac(struct bnxt *bp, u8 *mac)
{
	struct hwrm_func_vf_cfg_input req = {0};
	int rc = 0;

	if (!BNXT_VF(bp))
		return 0;

	if (bp->hwrm_spec_code < 0x10202) {
		if (is_valid_ether_addr(bp->vf.mac_addr))
			rc = -EADDRNOTAVAIL;
		goto mac_done;
	}
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_VF_CFG, -1, -1);
	req.enables = cpu_to_le32(FUNC_VF_CFG_REQ_ENABLES_DFLT_MAC_ADDR);
	memcpy(req.dflt_mac_addr, mac, ETH_ALEN);
	rc = hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
mac_done:
	if (rc) {
		rc = -EADDRNOTAVAIL;
		netdev_warn(bp->dev, "VF MAC address %pM not approved by the PF\n",
			    mac);
	}
	return rc;
}
