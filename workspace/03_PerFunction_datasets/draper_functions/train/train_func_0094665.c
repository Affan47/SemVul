axnet_resume(struct pcmcia_device *link)
{
	struct net_device *dev = link->priv;
	struct axnet_dev *info = PRIV(dev);

	if (link->open) {
		if (info->active_low == 1)
			pcmcia_write_config_byte(link, CISREG_CCSR, 0x04);

		axnet_reset_8390(dev);
		AX88190_init(dev, 1);
		netif_device_attach(dev);
	}

	return 0;
}
