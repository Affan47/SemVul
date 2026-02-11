aac_acquire_resources(struct aac_dev *dev)
{
	int i, j;
	int instance = dev->id;
	const char *name = dev->name;
	unsigned long status;


	while (!((status = src_readl(dev, MUnit.OMR)) & KERNEL_UP_AND_RUNNING)
		|| status == 0xffffffff)
			msleep(20);

	aac_adapter_disable_int(dev);
	aac_adapter_enable_int(dev);


	if ((dev->pdev->device == PMC_DEVICE_S7 ||
	     dev->pdev->device == PMC_DEVICE_S8 ||
	     dev->pdev->device == PMC_DEVICE_S9))
		aac_define_int_mode(dev);

	if (dev->msi_enabled)
		aac_src_access_devreg(dev, AAC_ENABLE_MSIX);

	if (!dev->sync_mode && dev->msi_enabled && dev->max_msix > 1) {
		for (i = 0; i < dev->max_msix; i++) {
			dev->aac_msix[i].vector_no = i;
			dev->aac_msix[i].dev = dev;

			if (request_irq(dev->msixentry[i].vector,
					dev->a_ops.adapter_intr,
					0, "aacraid", &(dev->aac_msix[i]))) {
				printk(KERN_ERR "%s%d: Failed to register IRQ for vector %d.\n",
						name, instance, i);
				for (j = 0 ; j < i ; j++)
					free_irq(dev->msixentry[j].vector,
						 &(dev->aac_msix[j]));
				pci_disable_msix(dev->pdev);
				goto error_iounmap;
			}
		}
	} else {
		dev->aac_msix[0].vector_no = 0;
		dev->aac_msix[0].dev = dev;

		if (request_irq(dev->pdev->irq, dev->a_ops.adapter_intr,
			IRQF_SHARED, "aacraid",
			&(dev->aac_msix[0])) < 0) {
			if (dev->msi)
				pci_disable_msi(dev->pdev);
			printk(KERN_ERR "%s%d: Interrupt unavailable.\n",
					name, instance);
			goto error_iounmap;
		}
	}

	aac_adapter_enable_int(dev);


	aac_fib_vector_assign(dev);

	if (!dev->sync_mode) {


		aac_adapter_start(dev);
		dev->init->Sa_MSIXVectors = cpu_to_le32(dev->max_msix);
	}
	return 0;

error_iounmap:
	return -1;

}
