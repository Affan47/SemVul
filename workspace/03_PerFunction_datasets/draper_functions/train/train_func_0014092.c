ipwireless_attach(struct pcmcia_device *link)
{
	struct ipw_dev *ipw;
	int ret;

	ipw = kzalloc(sizeof(struct ipw_dev), GFP_KERNEL);
	if (!ipw)
		return -ENOMEM;

	ipw->link = link;
	link->priv = ipw;

	ipw->hardware = ipwireless_hardware_create();
	if (!ipw->hardware) {
		kfree(ipw);
		return -ENOMEM;
	}


	ret = config_ipwireless(ipw);

	if (ret != 0) {
		ipwireless_detach(link);
		return ret;
	}

	return 0;
}
