ipr_log_fabric_path(struct ipr_hostrcb *hostrcb,
				struct ipr_hostrcb_fabric_desc *fabric)
{
	int i, j;
	u8 path_state = fabric->path_state;
	u8 active = path_state & IPR_PATH_ACTIVE_MASK;
	u8 state = path_state & IPR_PATH_STATE_MASK;

	for (i = 0; i < ARRAY_SIZE(path_active_desc); i++) {
		if (path_active_desc[i].active != active)
			continue;

		for (j = 0; j < ARRAY_SIZE(path_state_desc); j++) {
			if (path_state_desc[j].state != state)
				continue;

			if (fabric->cascaded_expander == 0xff && fabric->phy == 0xff) {
				ipr_hcam_err(hostrcb, "%s %s: IOA Port=%d\n",
					     path_active_desc[i].desc, path_state_desc[j].desc,
					     fabric->ioa_port);
			} else if (fabric->cascaded_expander == 0xff) {
				ipr_hcam_err(hostrcb, "%s %s: IOA Port=%d, Phy=%d\n",
					     path_active_desc[i].desc, path_state_desc[j].desc,
					     fabric->ioa_port, fabric->phy);
			} else if (fabric->phy == 0xff) {
				ipr_hcam_err(hostrcb, "%s %s: IOA Port=%d, Cascade=%d\n",
					     path_active_desc[i].desc, path_state_desc[j].desc,
					     fabric->ioa_port, fabric->cascaded_expander);
			} else {
				ipr_hcam_err(hostrcb, "%s %s: IOA Port=%d, Cascade=%d, Phy=%d\n",
					     path_active_desc[i].desc, path_state_desc[j].desc,
					     fabric->ioa_port, fabric->cascaded_expander, fabric->phy);
			}
			return;
		}
	}

	ipr_err("Path state=%02X IOA Port=%d Cascade=%d Phy=%d\n", path_state,
		fabric->ioa_port, fabric->cascaded_expander, fabric->phy);
}
