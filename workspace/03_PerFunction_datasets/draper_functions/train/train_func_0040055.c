airo_config(struct pcmcia_device *link)
{
	struct local_info *dev;
	int ret;

	dev = link->priv;

	dev_dbg(&link->dev, "airo_config\n");

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_VPP |
		CONF_AUTO_AUDIO | CONF_AUTO_SET_IO;

	ret = pcmcia_loop_config(link, airo_cs_config_check, NULL);
	if (ret)
		goto failed;

	if (!link->irq)
		goto failed;

	ret = pcmcia_enable_device(link);
	if (ret)
		goto failed;
	((struct local_info *)link->priv)->eth_dev =
		init_airo_card(link->irq,
			       link->resource[0]->start, 1, &link->dev);
	if (!((struct local_info *)link->priv)->eth_dev)
		goto failed;

	return 0;

 failed:
	airo_release(link);
	return -ENODEV;
}
