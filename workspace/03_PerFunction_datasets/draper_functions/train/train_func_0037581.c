alloc_dev(int adapter_num, int port_num, struct pci_dev *pdev)
{
	struct slgt_info *info;

	info = kzalloc(sizeof(struct slgt_info), GFP_KERNEL);

	if (!info) {
		DBGERR(("%s device alloc failed adapter=%d port=%d\n",
			driver_name, adapter_num, port_num));
	} else {
		tty_port_init(&info->port);
		info->port.ops = &slgt_port_ops;
		info->magic = MGSL_MAGIC;
		INIT_WORK(&info->task, bh_handler);
		info->max_frame_size = 4096;
		info->base_clock = 14745600;
		info->rbuf_fill_level = DMABUFSIZE;
		info->port.close_delay = 5*HZ/10;
		info->port.closing_wait = 30*HZ;
		init_waitqueue_head(&info->status_event_wait_q);
		init_waitqueue_head(&info->event_wait_q);
		spin_lock_init(&info->netlock);
		memcpy(&info->params,&default_params,sizeof(MGSL_PARAMS));
		info->idle_mode = HDLC_TXIDLE_FLAGS;
		info->adapter_num = adapter_num;
		info->port_num = port_num;

		setup_timer(&info->tx_timer, tx_timeout, (unsigned long)info);
		setup_timer(&info->rx_timer, rx_timeout, (unsigned long)info);


		info->pdev = pdev;
		info->irq_level = pdev->irq;
		info->phys_reg_addr = pci_resource_start(pdev,0);

		info->bus_type = MGSL_BUS_TYPE_PCI;
		info->irq_flags = IRQF_SHARED;

		info->init_error = -1;
	}

	return info;
}
