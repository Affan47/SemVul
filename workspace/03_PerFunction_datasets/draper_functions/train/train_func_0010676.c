tsi148_remove(struct pci_dev *pdev)
{
	struct list_head *pos = NULL;
	struct list_head *tmplist;
	struct vme_master_resource *master_image;
	struct vme_slave_resource *slave_image;
	struct vme_dma_resource *dma_ctrlr;
	int i;
	struct tsi148_driver *bridge;
	struct vme_bridge *tsi148_bridge = pci_get_drvdata(pdev);

	bridge = tsi148_bridge->driver_priv;


	dev_dbg(&pdev->dev, "Driver is being unloaded.\n");


	for (i = 0; i < 8; i++) {
		iowrite32be(0, bridge->base + TSI148_LCSR_IT[i] +
			TSI148_LCSR_OFFSET_ITAT);
		iowrite32be(0, bridge->base + TSI148_LCSR_OT[i] +
			TSI148_LCSR_OFFSET_OTAT);
	}


	iowrite32be(0, bridge->base + TSI148_LCSR_LMAT);


	iowrite32be(0, bridge->base + TSI148_LCSR_CSRAT);


	iowrite32be(0xFFFFFFFF, bridge->base + TSI148_LCSR_EDPAT);
	iowrite32be(0xFFFFFFFF, bridge->base + TSI148_LCSR_VEAT);
	iowrite32be(0x07000700, bridge->base + TSI148_LCSR_PSTAT);


	if (ioread32be(bridge->base + TSI148_LCSR_VICR) & 0x800)
		iowrite32be(0x8000, bridge->base + TSI148_LCSR_VICR);


	iowrite32be(0x0, bridge->base + TSI148_LCSR_INTM1);
	iowrite32be(0x0, bridge->base + TSI148_LCSR_INTM2);

	tsi148_irq_exit(tsi148_bridge, pdev);

	vme_unregister_bridge(tsi148_bridge);

	tsi148_crcsr_exit(tsi148_bridge, pdev);


	list_for_each_safe(pos, tmplist, &tsi148_bridge->dma_resources) {
		dma_ctrlr = list_entry(pos, struct vme_dma_resource, list);
		list_del(pos);
		kfree(dma_ctrlr);
	}


	list_for_each_safe(pos, tmplist, &tsi148_bridge->slave_resources) {
		slave_image = list_entry(pos, struct vme_slave_resource, list);
		list_del(pos);
		kfree(slave_image);
	}


	list_for_each_safe(pos, tmplist, &tsi148_bridge->master_resources) {
		master_image = list_entry(pos, struct vme_master_resource,
			list);
		list_del(pos);
		kfree(master_image);
	}

	iounmap(bridge->base);

	pci_release_regions(pdev);

	pci_disable_device(pdev);

	kfree(tsi148_bridge->driver_priv);

	kfree(tsi148_bridge);
}
