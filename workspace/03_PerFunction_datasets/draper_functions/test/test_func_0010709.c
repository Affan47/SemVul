sr_read_rx_ctl(struct usbnet *dev)
{
	__le16 v;
	int ret;

	ret = sr_read_cmd(dev, SR_CMD_READ_RX_CTL, 0, 0, 2, &v);
	if (ret < 0) {
		netdev_err(dev->net, "Error reading RX_CTL register:%02x\n",
			   ret);
		goto out;
	}

	ret = le16_to_cpu(v);
out:
	return ret;
}
