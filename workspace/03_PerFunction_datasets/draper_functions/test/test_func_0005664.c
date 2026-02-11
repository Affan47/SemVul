bnxt_hwrm_ver_get(struct bnxt *bp)
{
	int rc;
	struct hwrm_ver_get_input req = {0};
	struct hwrm_ver_get_output *resp = bp->hwrm_cmd_resp_addr;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VER_GET, -1, -1);
	req.hwrm_intf_maj = HWRM_VERSION_MAJOR;
	req.hwrm_intf_min = HWRM_VERSION_MINOR;
	req.hwrm_intf_upd = HWRM_VERSION_UPDATE;
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (rc)
		goto hwrm_ver_get_exit;

	memcpy(&bp->ver_resp, resp, sizeof(struct hwrm_ver_get_output));

	if (req.hwrm_intf_maj != resp->hwrm_intf_maj ||
	    req.hwrm_intf_min != resp->hwrm_intf_min ||
	    req.hwrm_intf_upd != resp->hwrm_intf_upd) {
		netdev_warn(bp->dev, "HWRM interface %d.%d.%d does not match driver interface %d.%d.%d.\n",
			    resp->hwrm_intf_maj, resp->hwrm_intf_min,
			    resp->hwrm_intf_upd, req.hwrm_intf_maj,
			    req.hwrm_intf_min, req.hwrm_intf_upd);
		netdev_warn(bp->dev, "Please update driver or firmware with matching interface versions.\n");
	}
	snprintf(bp->fw_ver_str, BC_HWRM_STR_LEN, "bc %d.%d.%d rm %d.%d.%d",
		 resp->hwrm_fw_maj, resp->hwrm_fw_min, resp->hwrm_fw_bld,
		 resp->hwrm_intf_maj, resp->hwrm_intf_min, resp->hwrm_intf_upd);

hwrm_ver_get_exit:
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}
