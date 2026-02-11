sr_get_phy_addr(struct usbnet *dev)
{
	u8 buf[2];
	int ret;

	ret = sr_read_cmd(dev, SR_CMD_READ_PHY_ID, 0, 0, 2, buf);
	if (ret < 0) {
		netdev_err(dev->net, "%s : Error reading PHYID register:%02x\n",
			   __func__, ret);
		goto out;
	}
	netdev_dbg(dev->net, "%s : returning 0x%04x\n", __func__,
		   *((__le16 *)buf));

	ret = buf[1];

out:
	return ret;
}
