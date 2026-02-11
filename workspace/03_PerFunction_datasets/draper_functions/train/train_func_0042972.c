be_get_regs(struct net_device *netdev, struct ethtool_regs *regs, void *buf)
{
	struct be_adapter *adapter = netdev_priv(netdev);

	if (be_physfn(adapter)) {
		memset(buf, 0, regs->len);
		if (lancer_chip(adapter))
			lancer_cmd_read_file(adapter, LANCER_FW_DUMP_FILE,
					     regs->len, buf);
		else
			be_cmd_get_regs(adapter, regs->len, buf);
	}
}
