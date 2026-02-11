vlsi_open(struct net_device *ndev)
{
	vlsi_irda_dev_t *idev = netdev_priv(ndev);
	int	err = -EAGAIN;
	char	hwname[32];

	if (pci_request_regions(idev->pdev, drivername)) {
		net_warn_ratelimited("%s: io resource busy\n", __func__);
		goto errout;
	}
	ndev->base_addr = pci_resource_start(idev->pdev,0);
	ndev->irq = idev->pdev->irq;


	outb(IRINTR_INT_MASK, ndev->base_addr+VLSI_PIO_IRINTR);

	if (request_irq(ndev->irq, vlsi_interrupt, IRQF_SHARED,
			drivername, ndev)) {
		net_warn_ratelimited("%s: couldn't get IRQ: %d\n",
				     __func__, ndev->irq);
		goto errout_io;
	}

	if ((err = vlsi_create_hwif(idev)) != 0)
		goto errout_irq;

	sprintf(hwname, "VLSI-FIR @ 0x%04x", (unsigned)ndev->base_addr);
	idev->irlap = irlap_open(ndev,&idev->qos,hwname);
	if (!idev->irlap)
		goto errout_free_ring;

	idev->last_rx = ktime_get();

	idev->new_baud = 9600;

	if ((err = vlsi_start_hw(idev)) != 0)
		goto errout_close_irlap;

	netif_start_queue(ndev);

	net_info_ratelimited("%s: device %s operational\n",
			     __func__, ndev->name);

	return 0;

errout_close_irlap:
	irlap_close(idev->irlap);
errout_free_ring:
	vlsi_destroy_hwif(idev);
errout_irq:
	free_irq(ndev->irq,ndev);
errout_io:
	pci_release_regions(idev->pdev);
errout:
	return err;
}
