hw_sm750_map(struct sm750_dev *sm750_dev, struct pci_dev *pdev)
{
	int ret;

	ret = 0;

	sm750_dev->vidreg_start  = pci_resource_start(pdev, 1);
	sm750_dev->vidreg_size = SZ_2M;

	pr_info("mmio phyAddr = %lx\n", sm750_dev->vidreg_start);


	ret = pci_request_region(pdev, 1, "sm750fb");
	if (ret) {
		pr_err("Can not request PCI regions.\n");
		goto exit;
	}


	sm750_dev->pvReg = ioremap_nocache(sm750_dev->vidreg_start,
					   sm750_dev->vidreg_size);
	if (!sm750_dev->pvReg) {
		pr_err("mmio failed\n");
		ret = -EFAULT;
		goto exit;
	} else {
		pr_info("mmio virtual addr = %p\n", sm750_dev->pvReg);
	}


	sm750_dev->accel.dprBase = sm750_dev->pvReg + DE_BASE_ADDR_TYPE1;
	sm750_dev->accel.dpPortBase = sm750_dev->pvReg + DE_PORT_ADDR_TYPE1;

	ddk750_set_mmio(sm750_dev->pvReg, sm750_dev->devid, sm750_dev->revid);

	sm750_dev->vidmem_start = pci_resource_start(pdev, 0);


	sm750_dev->vidmem_size = ddk750_getVMSize();
	pr_info("video memory phyAddr = %lx, size = %u bytes\n",
		sm750_dev->vidmem_start, sm750_dev->vidmem_size);


	sm750_dev->pvMem = ioremap_wc(sm750_dev->vidmem_start,
				      sm750_dev->vidmem_size);
	if (!sm750_dev->pvMem) {
		pr_err("Map video memory failed\n");
		ret = -EFAULT;
		goto exit;
	} else {
		pr_info("video memory vaddr = %p\n", sm750_dev->pvMem);
	}
exit:
	return ret;
}
