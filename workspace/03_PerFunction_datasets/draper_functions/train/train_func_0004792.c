mtip_hw_resume(struct driver_data *dd)
{

	hba_setup(dd);


	if (mtip_hba_reset(dd) != 0) {
		dev_err(&dd->pdev->dev,
			"Unable to reset the HBA\n");
		return -EFAULT;
	}


	mtip_init_port(dd->port);
	mtip_start_port(dd->port);


	writel(readl(dd->mmio + HOST_CTL) | HOST_IRQ_EN,
			dd->mmio + HOST_CTL);

	return 0;
}
