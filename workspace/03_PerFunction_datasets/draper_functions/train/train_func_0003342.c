config_ipwireless(struct ipw_dev *ipw)
{
	struct pcmcia_device *link = ipw->link;
	int ret = 0;

	ipw->is_v2_card = 0;
	link->config_flags |= CONF_AUTO_SET_IO | CONF_AUTO_SET_IOMEM |
		CONF_ENABLE_IRQ;

	ret = pcmcia_loop_config(link, ipwireless_probe, ipw);
	if (ret != 0)
		return ret;

	INIT_WORK(&ipw->work_reboot, signalled_reboot_work);

	ipwireless_init_hardware_v1(ipw->hardware, link->resource[0]->start,
				    ipw->attr_memory, ipw->common_memory,
				    ipw->is_v2_card, signalled_reboot_callback,
				    ipw);

	ret = pcmcia_request_irq(link, ipwireless_interrupt);
	if (ret != 0)
		goto exit;

	printk(KERN_INFO IPWIRELESS_PCCARD_NAME ": Card type %s\n",
			ipw->is_v2_card ? "V2/V3" : "V1");
	printk(KERN_INFO IPWIRELESS_PCCARD_NAME
		": I/O ports %pR, irq %d\n", link->resource[0],
			(unsigned int) link->irq);
	if (ipw->attr_memory && ipw->common_memory)
		printk(KERN_INFO IPWIRELESS_PCCARD_NAME
			": attr memory %pR, common memory %pR\n",
			link->resource[3],
			link->resource[2]);

	ipw->network = ipwireless_network_create(ipw->hardware);
	if (!ipw->network)
		goto exit;

	ipw->tty = ipwireless_tty_create(ipw->hardware, ipw->network);
	if (!ipw->tty)
		goto exit;

	ipwireless_init_hardware_v2_v3(ipw->hardware);


	ret = pcmcia_enable_device(link);
	if (ret != 0)
		goto exit;

	return 0;

exit:
	if (ipw->common_memory) {
		release_mem_region(link->resource[2]->start,
				resource_size(link->resource[2]));
		iounmap(ipw->common_memory);
	}
	if (ipw->attr_memory) {
		release_mem_region(link->resource[3]->start,
				resource_size(link->resource[3]));
		iounmap(ipw->attr_memory);
	}
	pcmcia_disable_device(link);
	return -1;
}
