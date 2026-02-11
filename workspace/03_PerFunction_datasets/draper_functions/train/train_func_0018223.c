p54u_firmware_reset_3887(struct ieee80211_hw *dev)
{
	struct p54u_priv *priv = dev->priv;
	u8 *buf;
	int ret;

	buf = kmemdup(p54u_romboot_3887, 4, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	ret = p54u_bulk_msg(priv, P54U_PIPE_DATA,
			    buf, 4);
	kfree(buf);
	if (ret)
		dev_err(&priv->udev->dev, "(p54usb) unable to jump to "
			"boot ROM (%d)!\n", ret);

	return ret;
}
