lbtf_update_hw_spec(struct lbtf_private *priv)
{
	struct cmd_ds_get_hw_spec cmd;
	int ret = -1;
	u32 i;

	lbtf_deb_enter(LBTF_DEB_CMD);

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	memcpy(cmd.permanentaddr, priv->current_addr, ETH_ALEN);
	ret = lbtf_cmd_with_response(priv, CMD_GET_HW_SPEC, &cmd);
	if (ret)
		goto out;

	priv->fwcapinfo = le32_to_cpu(cmd.fwcapinfo);


	priv->fwrelease = le32_to_cpu(cmd.fwrelease);
	priv->fwrelease = (priv->fwrelease << 8) |
		(priv->fwrelease >> 24 & 0xff);

	printk(KERN_INFO "libertastf: %pM, fw %u.%u.%up%u, cap 0x%08x\n",
		cmd.permanentaddr,
		priv->fwrelease >> 24 & 0xff,
		priv->fwrelease >> 16 & 0xff,
		priv->fwrelease >>  8 & 0xff,
		priv->fwrelease       & 0xff,
		priv->fwcapinfo);
	lbtf_deb_cmd("GET_HW_SPEC: hardware interface 0x%x, hardware spec 0x%04x\n",
		    cmd.hwifversion, cmd.version);


	priv->regioncode = le16_to_cpu(cmd.regioncode) & 0xFF;

	for (i = 0; i < MRVDRV_MAX_REGION_CODE; i++) {

		if (priv->regioncode == lbtf_region_code_to_index[i])
			break;
	}


	if (i >= MRVDRV_MAX_REGION_CODE) {
		priv->regioncode = 0x10;
		pr_info("unidentified region code; using the default (USA)\n");
	}

	if (priv->current_addr[0] == 0xff)
		memmove(priv->current_addr, cmd.permanentaddr, ETH_ALEN);

	SET_IEEE80211_PERM_ADDR(priv->hw, priv->current_addr);

	lbtf_geo_init(priv);
out:
	lbtf_deb_leave(LBTF_DEB_CMD);
	return ret;
}
