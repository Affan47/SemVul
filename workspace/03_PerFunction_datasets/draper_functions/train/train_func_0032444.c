ipw_send_card_disable(struct ipw_priv *priv, u32 phy_off)
{
	__le32 v = cpu_to_le32(phy_off);
	if (!priv) {
		IPW_ERROR("Invalid args\n");
		return -1;
	}

	return ipw_send_cmd_pdu(priv, IPW_CMD_CARD_DISABLE, sizeof(v), &v);
}
