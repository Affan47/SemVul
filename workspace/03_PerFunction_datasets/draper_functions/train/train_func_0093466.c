ezusb_docmd_wait(struct hermes *hw, u16 cmd, u16 parm0,
			    struct hermes_response *resp)
{
	struct ezusb_priv *upriv = hw->priv;
	struct request_context *ctx;

	__le16 data[4] = {
		cpu_to_le16(cmd),
		cpu_to_le16(parm0),
		0,
		0,
	};
	netdev_dbg(upriv->dev, "0x%04X, parm0 0x%04X\n", cmd, parm0);
	ctx = ezusb_alloc_ctx(upriv, EZUSB_RID_DOCMD, EZUSB_RID_ACK);
	if (!ctx)
		return -ENOMEM;

	return ezusb_access_ltv(upriv, ctx, sizeof(data), &data,
				EZUSB_FRAME_CONTROL, NULL, 0, NULL);
}
